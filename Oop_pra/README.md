# 如何理解类值行为和类指针行为？
## 行为像值的类
为了提供类值的行为，对于**类管理的资源，每个对象都应该拥有一份自己的拷贝**。
```cpp
class HasPtr{
public:
    //some functions
private:
    std::string *ps;
    int i;
}
```
那么对于`HasPtr`类来说，为了实现类值行为，HasPtr需要：
- 定义一个拷贝构造函数，拷贝string的值，而不是拷贝指针。
- 定义一个析构函数来释放string
- 定义一个拷贝赋值运算符来释放对象当前的string，并从右侧对象拷贝string。

### 类值拷贝复制元素赋值运算符
&emsp;&emsp;赋值运算符通常**组合了析构函数和构造函数的操作**，类似析构函数，赋值操作会销毁左侧运算对象的资源。类似拷贝构造函数，赋值操作会从右侧运算对象拷贝数据。  
这些操作都是以正确的顺序执行的，即使将**一个对象赋予自身，也能保证正确**。


## 行为像指针的类
&emsp;&emsp;定义拷贝构造函数和拷贝赋值运算符，来拷贝**指针成员本身而不是它指向的string**。类仍需要自己的析构函数来释放接受string参数的构造函数分配的内存，但是不能单方面的释放关联的string，只有**最后一个指向string的HasPtr销毁时参考一释放string**。  
&emsp;&emsp;令一个类**展现指针的最好方法就是使用`shared+ptr`**来管理类中的资源，当没有用户使用对象时，`shared_ptr`类负责释放资源。

### 如何直接管理资源而不使用智能指针：
&emsp;&emsp;使用**引用计数**：
&emsp;&emsp;引用计数的工作方式如下：
- 除了初始化对象外，每个构造函数（拷贝构造函数除外）还要创建一个**引用计数**，用来记录多少对象**与正在创建的对象**共享状态，创建对象的时候将计数器初始化为1.
- 拷贝构造函数**不分配新的计数器**，而是拷贝给定对象的数据成员，包括计数器。拷贝构造函数递增共享的计数器，指出给定对象的状态又被一个新用户所共享。
- 析构函数递减计数器，只存储共享状态的用户少了一个。如果计数器变为0，则析构函数释放状态。

```cpp
class HasPtr{
public:
    HasPtr(const std::string &s=std::string()):ps(new std::string(s)),i(0),
        count(new std::size_t(1)){};
    HasPtr(const HasPtr &p):
        ps(p.ps),i(p.i),count(p,count){++*count;}
    HasPtr& operator=(const HasPtr &rhs){
        ++*rhs.count;
        if(--*count==0){
            delete ps;
            delete count;
        }
        ps=rhs.ps;
        i=rhs.i;
        count=rhs.count;
        return *this;
    }
    ~HasPtr(){
        if(--*count){
            delete ps;
            delete count;
        }
    }
private:
    std::string *ps;
    int i;
    //在构造函数中动态分配就可以啦
    std::size_t* count;
}
```

- 当拷贝或赋值一个HasPtr对象时，我们希望副本和原对象都指向相同的string。那么就考呗指针而非string值。


## 如何区分行为像指针的类与像值得类？
- 如果存在使用智能指针，或者有引用计数这个东西的话，就很明显是把类当作指针行为
- 如果对于每个资源都进行另行复制，那么就是希望这个类有值行为。、
- 当然，面对自己设计的类的时候，究竟是选择具有值行为还是指针行为，还是需要仔细分析才对。



# 习题练习精选：
### 什么时候使用拷贝构造函数？
- 拷贝初始化，传递给非引用类型形参，**返回值为非引用类型**的对象，**初始化标准容器或调用push/insert操作的时候。
### 拷贝构造函数如何工作？
&emsp;&emsp;合成的拷贝构造函数逐个拷贝非const成员，对内置类型成员直接进行内存拷贝。对类类型成员调用其拷贝构造函数进行拷贝。

### 13.5 
```cpp
HasPtr(const HasPtr& org){
    i=org.i;
    ps=new string(*org.ps);
}
```
### 13.6
&emsp;&emsp;通常情况下，合成的拷贝赋值运算符会将右侧对象**非static成员诸葛赋予右侧对象的对应成员**。这些赋值操作是由成员类型的拷贝赋值运算符来完成的。
若未定义会自动合成。

### 13.8
&emsp;&emsp;赋值运算符和拷贝构造函数的写法就不太一样了，因为赋值运算符的左侧运算对象已经有值了，现在我需要把它的值给替换掉。
```cpp
HasPtr& operator=(const HasPtr& org){
    i=org.i;
    auto newps=new string(*org.ps);

    //这个是不是必须的呢？为什么不能进行重新赋值？
    delete ps;//构造函数里面这个指针是动态分配的
    ps=newps;
    return *this;
}
```

### 13.9
&emsp;&emsp;析构函数释放对象使用的资源，销毁非静态数据成员。合成的析构函数执行完后，非静态数据成员会被诸葛销毁。**成员是在析构函数体之后隐含的析构阶段中进行销毁的**。

### 13.12
下面代码片段产生几次析构函数调用：
```cpp
bool func(const Sale_data *trans,Sale_data accum){
    Sale_data item1(*trans),item2(accum);
    return item1.isbn()!=item2.isbn();
}
```
- item1与item2的析构函数调用
- ~~trans与~~accum的析构函数调用
&emsp;&emsp;虽然`trans`的生命周期也结束了，但它是一个指针，并不是**它指向的对象的生命期结束**，所以不会调用析构函数。

### 13.14
```cpp
//有一个类numbered为每个对象生成唯一的序号，保存在mysn中
//有一个函数：
void func(numbered s){cout<<s.mysn<<endl;}
numbered a,b=a,c=b;
func(a);
func(b);
func(c);
```
&emsp;&emsp;对以上的代码来说，如果定义了拷贝构造函数，那么输出的值就不会相同。但是注意**在函数实参与形参传递的时候调用了拷贝构造函数，形参这个临时对象被分配了新的值**。
