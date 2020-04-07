# 15.9 & 12.3

## 12.3：`TextQuery`与`QueryResult`
&emsp;&emsp;在查询的时候，其实就是把每个单词放到一个map里面去，mao存储了这个单词和所在的对应的行号，若一行有多个相同字符，那么只会存储一个。  
&emsp;&emsp;使用一个vector存储每行的内容，下标对应行号。

## map
### find
Get iterator to element  
Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.


# 15.9 查询字符串再探：
