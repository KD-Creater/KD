1-4
平常所说的Oracle或Oracle数据库指的是Oracle数据库管理系统
那么它由两部分构成，即Oracle数据库和Oracle实例
1-5 SQL Plus 常用命令
desc
col[umn]
pass[word]
connect username/password
show user
host<dos 命令>  SQL> host mkdir d:\OracleTest;
spool:导出记录到文件 SQL> spool d:\OracleTest\test.txt;
					 SQL> select * from tablename;
					 SQL> spool off；
clear screen:清屏
start:执行脚本		SQL>start d:\test.sql;
show error:显示错误信息
exit:退出
2-1 系统用户登录Oracle
Oracle 默认的系统用户:sys 只能以系统管理员或者系统操作者来登录 
					  system
					  sysman是Oracle数据库中用来EM管理的用户
					  scott是Oracle提供的示例用户，里面有一些供初学者学习操作的数据表
					  (emp,dept,salgrade,bonus)
Oracle用户登录
{<username>[/password][@<connect_identifier>]} | [as{sysdba | sysoper}]
1>username/password 指定数据库账户名和口令
2>connect_identifier 数据库连接的连接标识符(服务器名)，如果没有连接标识符，SQL*Plus连接到默认数据库
3>sysdba:数据库管理员权限	sysoper:数据库操作员权限

启用scott用户
给用户解锁: alter user username account unlock;(以sys用户权限登录)
SQL>alter user scott account unlock;
SQL>conn scott/tiger;
SQL>select table_name from user_tables;(查看当前状态下所有的表信息)

2-2 表空间
创建表空间
create[temporary]tablespace tablespace_name tempfile|datafile 'xxx.dbf' size xx;
SQL>create tablespace test1_tablespace datafile 'test1file.dbf' size 10m;
SQL>create temporary tablespace temptest1_tablespace tempfile 'tempfile1.dbf' size 10m
SQL>select file_name from dba_data_files where tablespace_name = 'TEST1_TABLESPACE';查看表空间的位置
SQL>select file_name from dba_temp_files where tabelspace_name = 'TEMPTEST1_TABLESPACE';查看临时表空间的位置

2-3 创建用户
create user <user_name> identified by <password> default <default tablespace>
temporary tablespace <temporary tablespace>;
select username from dba_users; (查看系统所有的用户名)
给创建的用户授权
grant 权限to 用户名
SQL>grant connect to yan;(给用户yan授予连接的权限)
管理用户
1>连接用户
connect 用户名/口令
2>更改密码
alter user 用户名 identified by 新密码
>3不希望某用户登录，而又不删除其用户，可以将用户锁定
alter user 用户名 account lock;
4>删除用户
drop user 用户名 cascade //加上cascade则将用户连同创建的东西全部删除

2-4 角色
Oracle 角色（role）就是一组权限（或者说是权限的集合）
用户可以给角色授予指定的权限，然后给角色赋予相应的用户
3种标准权限
1>connect(连接角色)
拥有connect权限的用户只可以登录oracle,不可以创建实体，不可以创建数据库结构
2>resource(资源角色)
拥有resource权限的用户只可以创建实体，不可以创建数据库结构
3>dba（数据库管理员角色）
拥有全部特权，是系统最高权限，只有DBA才可以创建数据库结构
对于普通用户：授予connect,resource权限
对于DBA管理用户：授予DBA权限
SQL>conn  as/sysdba		
SQL>create user user01 identified by 1	//不指定表空间默认使用系统表空间，不建议这样做，容易是系统表空间被沾满，导致宕机
SQL>grant connect to user01
SQL>grant resource to user01
SQL>conn user01/1
SQL>create table test(id number, name varchar2(200));
SQL>conn sys/1 as sysdba
SQL>grant dba to user01
SQL>create user user02 identified by 1
创建角色
create role 角色名
SQL>create role manager
为角色赋予权限
grant 权限 to 角色
SQL>grant create table,create view to manager
将角色赋予用户
grant 角色 to 用户
SQL>grant manager to user01 ,user02;
收回权限
SQL>revoke manager from user 02;
删除角色
SQL>drop role manager
2-5用户的权限管理
权限指的是执行特定命令或者访问数据库对象的权利
权限的分类
系统权限：允许用户执行特定的数据库动作，如创建表，创建索引，创建实例等
对象（实体）权限：允许用户操纵一些特定的对象，如读取视图，更新某些列，执行存储过程等。
查看Oracle 的所有系统权限
SQL>select * from system_privilege_map
授予系统权限的语法格式
grant privilege[,pribilege...] to user [,user|role,public...]
SQL>grant create table, create sequence to manager;
SQL>grant manager to user01,user02;
回收系统权限的语法格式
revoke{privilege | role} from {user_name | role_name | public}
SQL>revoke manager from user01;
SQL>revoke create table,create sequence from manager;
对象权限
查询Oracle 所有的对象权限
SQL>select * from table_privilege_map;
常用的对象权限如：select ,update, insert, delete, all 等//all为所有权限
授予对象权限的语法格式
grant object_priv | all [(columns) on object to {user|role|public}]
SQL>grant select, update, insert on scott.emp to manager2;
SQL>grant manager2 to user03;
SQL>grant all on scott.emp to user04;
回收对象权限的语法格式
revoke{privilege[,privilege...] | all} on object from {user[,user...] | role public}
SQL>revoke all on scott.emp frim user04;
2-6 表空间管理
相关的数据字典
1>dab_tablespaces
2>user_tablespaces
3>dba_users
4>user_users
SQL>select tablespace_name from dba_tablespaces;
SQL>select default_tablespace, temporary_tablespace from user_users where username = 'SYSTEM';
设置用户默认或者临时表空间
1>alter user username deflaut | temporary tablespace tablespace_name;
SQL>alter user user01 defalut tablespace test01_tablespace 
修改表空间的状态
alter tablespace tablesapce_name online | offline | read only | read write  (=online);
如果一个表空间设置成脱机状态，表示该表空间暂时不让访问，并不是删除，设置成联机状态，可正常使用。
默认是可读可写状态
添加/删除数据文件
alter tablespace tablespce_name add datafile'filename.dbf' 
alter tablespace tablespace_name drop dataflie 'fliename.dbf';
SQL>alter tablespace test01_tablespace add datafile 'test02_dataflie.dbf' size 10m;
SQL>select file_name from dba_data_files where tablespace_name = 'test01_tablespace';
不能删除表空间中的第一个创建的数据文件，如果需要删除，我们要把整个表空间删除掉
删除表空间
drop tablespace tablespace_name[includind contents];
如果删除时只想单纯的删除表空间，而不删除数据文件的话，可以:drop tablespace tablespace_name;
如果想连数据文件一起删除时，要添加 including contents
3-2
DDL(data definition language)数据定义语言
-create table:创建表
-create index:创建索引
-drop table
-drop index
-truncate:删除表中的所有行
-alter table:更改表结构，增加，更改，删除列
-alter table add constraint:在已有的表上增加约束
DML(data maniulation language)数据操作语言
-insert
-update
-delete
-select
DCL(data control language)数据控制语言
-grant
-revoke
-lock
TCL(transation control language)事务控制语言
-commit:提交事务处理
-rollback:事务处理回退
-savepoint:设置保存点
3-3 创建表
create table table_name(
	colum_name datetype
) 
数据类型
字符类型:
char:表示固定长度的字符串，列长度可以时1到2000个字节
varchar2:表示可变长度的字符串，最大长度为4000字节
number[(p[,s])]:p表示精度，s表示小数点的位数，可以存储整数，浮点数等数值类型，最高精度为38位
eg:number(5,0)最多可以存储五位整数
	number(5,2)最大可存储999.99的浮点数
date:日期类型
lob:
1>clob即character lob:它能够存储大量字符数据
2>blob即binary lob:它可以存储较大的二进制对象，如图形，视频剪辑和声音文件等
3-4 约束
约束是oracle提供的自动保持数据库完整性的一种方法，它通过限制字段中的数据，记录数据和表之间的数据来
保证数据的完整性。
完整性约束的语法为
[constraint constraint_name]<约束类型>--约束不指定名称时，系统会给定一个名称。
oracle 中的约束:
主键约束(primary key constraint)
primary key 约束用于定义表的主键，它是唯一确定表中每一条记录的标识符，其值不能为空，也不能重复，以此来确定实体的完整性、
。表中主键只能有一个，但可以由多个列构成，如primary key(学号，科目编号)。
添加主键约束:
创建表时加主键约束
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20),
SQL>csex char(2),
SQL>caddr varchar2(50),
SQL>cbrith date，
SQL>cconstriant sid_pk primary key(sid)
);
修改表添加主键约束
alter table student add constraint sid_pk primary key (sid);
唯一性约束(unique constraint)
默认约束(defalut constraint)
非空约束(not null constriant)
检查约束(check constriant)
外部约束(foreign key constraint)
3-5 非空约束
not null 约束用于确保列不能为NULL，如果定义了not null约束，那么当插入数据时，必须为该列提供数据，
当更新数据时，不能将其值设置为NULL。
非空约束是列级约束
列级约束:
column [constraint constraint_name] constraint_type,
说名:列级约束必须跟在列的定义后面
表级约束:
[constraint constraint_name] constriant_type
说明:表级约束不与列级一起，而是单独定义的。
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) constraint nn_sex not null, --列级约束
SQL>caddr varchar2(50),
SQL>cbrith date，
SQL>cconstriant sid_pk primary key(sid) --表级约束
);
修改表添加约束的格式对比
1>修改表添加约束的语法格式:
alter table table_name add [constraint constriant_name] constraint_type(column);
2>而添加not null 约束要使用modify
alter table table_name modify (column datatype not null);
删除约束的方式
1>将约束无效化或者激活
disable | enable constraint constraint_name
2>将约束彻底删除
drop constriant constraint_name
>删除主键约束的格式：
drop primary key
>删除非空约束的方式
alter table table_name modify column_name datatype null;
SQL>alter table student disable constrinat pk_sid;
SQL>alter table student drop constraint pk_sid;
SQL>alter table student drop primary key;
3-6 唯一约束
唯一性约束用于指定一个或者多个列的组合值具有唯一性，以防止在列中输入重复的值
注意:
>使用唯一性约束的列允许为空值
>一个表中可以允许有多个唯一性约束
>可以把唯一性约束定义在多个列上
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) constraint nn_sex not null, --列级约束
SQL>caddr varchar2(50),
SQL>cbrith date，
SQL>cconstriant sid_pk primary key(sid) --表级约束
SQL>cardid varchar2(18),
SQL>email varchar2(50) unique,
constraint uk_cardid unique(cardid)
);
修改表时添加唯一性约束
alter table student add constraint uk_cardid unique(cardid);
禁用约束
alter table student disable constraint uk_cardid;
删除约束
alter table student drop constraint uk_cardid;
3-7 检查约束
检查约束对输入列或者整个表中的值设置检查条件，以限制输入值，保证数据库数据的完整性。
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) check(sex='男' or '女'), --列级约束
SQL>caddr varchar2(50),
SQL>cbrith date，
SQL>cconstriant sid_pk primary key(sid) --表级约束
SQL>cardid varchar2(18),
SQL>email varchar2(50) unique,
SQL>constraint ck_sex check (sex='男' or '女')；
)

alter table student add constraint ck_sex check(sex = '男' or '女')；
alter table student disable constraint ck_sex;
alter table student drop constraint ck_sex;
3-8外键约束
外键约束(foreign key), 	是用于建立和加强两个表之间的链接的一列或者多列。外键约束是唯一涉及两个表关系的约束
设置外键约束的语法格式(主表已存在，创建从表时设置)
create table 从表(column_name datatype references 主表(column_name) [on delete cascade],...);
constraint constraint_name foreign key (column_name) references 主表 (column_name)[on delete cascade]
创建主表:
create table department(depid varchar2(20) primary key,
depname varchar2(30));
创建从表
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) constraint nn_sex not null, --列级约束
SQL>caddr varchar2(50),
SQL>cbrith date，
SQL>depid varchar2(10) references department(depid);
SQL>constriant fk_depid foreign key(depid) references department(depid) on delete cascade --表级约束
);
注意事项
设置外键约束时主表的字段必须是主键列(或唯一列)
主从表相应字段必须是同一数据类型
从表中外键字段的值必须来自主表中的相应字段的值，或者为NULL值。
alter table student add constraint fk_depid foreign key(depid) references department(depid) on delete cascade; 
3-9 Oracle的表操作--修改和删除表DDL
alter table 表名 add  新增列名 数据类型
SQL>alter table student add tel varchar2(20);
alter table 表明 modify 列名 新数据类型
SQL>alter table student modify tel number(20,0);
alter table 表名 drop column 列名
SQL>alter table student drop colum tel;
alter table 表名 rename column 列名 to 新列名
SQL>alter table student rename  column sex to gender;
rename 表明 to 新表名
SQL>rename student to studentinfo;
truncate table 表名;
truncate table操作用于删除表中的全部数据，并不是吧表删除掉，这种方式要比delete方式删除数据要快，
也叫截断表
drop table 表名;删除表结构
3-10 Oracle的表操作--增删改查 dml
insert into 表名[列1,列2,...列n]values(值1，值2...,值n)
SQL>insert into student(sid,name,sex) values(2001001,'张三','女');
SQL>insert into student(sid,name,sex,address,birhday)values(20010002,'wangwu','beijing',to_date('19820909','YYYYMMDD'))；
select * | column[列名] from 表名;
update table set column = value [,column = value,...] [where condition];
delete from table [where condition];
3-11 Oracle的表操作--事务
什么是事务?
事务可以看作是由对数据库的若干操作组成的一个单元，这些操作要么都完成，要么都取消，从而保证数据满足
一致性的要求。
事务的组成：
>一条或者多条DML
>一条DDL
>一条DCL
DML语句需要使用commit 提交事务或者使用rollback回滚事务
DDL，DCL是自动提交事务的
使用事务的原因：保证数据的安全有效
当执行事务操作(DML语句)时，Oracle会在被作用的表上加表锁，以防止其他用户改变表结构；同时会在被作用
的行上加行锁，以防止其他事务在对应行上执行DML操作。
提交事务（commit）
通过commit语句可以提交事务，当执行了commit语句后，会确认事务的变化，结束事务，删除保存点，释放锁
当使用commit语句结束事物后，其他会话将可以查到事务变化后新的数据。
回滚事务(rollback)
rollback只能对未提交的数据撤销，已经commit的数据是无法撤销的，因为commit之后已经持久化到数据库中。
保存点(savepoint)
是事务中的一点，用于取消部分事务，当结束事务时，会自动的删除该事务所定义的所有保存点，当执行rollback时
通过指定保存点可以回退到指定的点。
设置保存点：savepoint a;
回滚部分事务：rollback to a;
回滚全部事务：rollback;
3-12 数据字典
数据字典是Oracle存放有关数据库信息的地方，其用途是用来描述数据的，数据字典是一组表和视图结构
数据库中的表是不能直接被访问的，但是可以访问数据字典的视图
通过数据字典，使我们了解数据库内部的信息，当用户在对数据库中的数据进行操作时遇到困难就可以访问数据
字典来查看详细的信息
Oracle 中常用的数据字典分为三类，以三种前缀开头：
uesr_*
该视图存储了关于当前用户所拥有的对象的信息。（即所有在该用户模式下的对象）,
all_*
该视图存储了当前用户能够访问的对象信息（与user_*相比，all_*并不需要拥有该对象，只要具有访问该对象）的权限即可）,
dba_*
该视图存储了数据库中所有对象的信息。（前提是当前用户具有访问这些数据库的权限，一般来说必须具有管理员权限）
Oracle 常用的数据字典
user_users			关于用户的信息
user_tablespaces	
user_tables
user_views
user_sequences
user_constraints
user_triggers
user_source
4-1 Oracle的基本查询
select * | {[distinct] column | expression[alias],....} from table [where condition]

table 用于指定表名
column 用于指定列名
expression 表达式
alias 用于指定列的别名
condition 查询条件

排除重复行
select distinct deptno,job from emp;
查新日期列
日期列:是指数据类型为日期类型的列，如date类型
日期列的默认格式为DD_MON_RR
RR:代表年，而且只取年份的后两位数字。
以简体中文显示日期结果
如果以简体中文显示日期结果，那么可以将会话的nls_language 参数设置为simplified chinese
alter session set nls_language = 'simplified chinese';
如果以美国日期英语显示日期结果，那么可以将会话的nls_language参数设置为american.
alter session set nls_language='american';
如果希望定制日期显示格式，并按照特定方式显示日期结果，那么可以设置会话的nls_date_format参数
alter session set nls_date_format = 'YYYY/MM/DD';
算数运算符+-*/算数运算符可以应用在数字和日期的列上。
select empno,ename,sal,sal*12 from emp;
select empno, ename, sal*12 + sal/2 from emp;
在算数运算符中的空值NULL 表示未知值，它既不是空格也不是0
当算数表达式包含NULL时，其结果也为空(NULL).
空值:当插入数据时，如果没有为特定的列提供数据，并且该列没有默认值，那么其结果为NULL
默认值:在创建表时，可以使用default关键字为列设置默认值，在表中插入数据时，如果没有为该列提供数据，那么该列使用默认值/
create table student(sid number(8,0) primary key,name varchar2(10),sex char(2) default '男'，age number(2,0)default 20,address varchar2(50));
insert into student values(2001002,'wangwu',default,21,'beijing')
不使用列的别名
select empno,ename,sal*12 from emp;
使用列的别名
select empno "雇员编号", ename "雇员名", sal*12 "全年工资" from emp; 或者
select empno as "雇员编号", ename as "雇员名", sal*12 as "全年工资" from emp; 或者
select empno 雇员编号, ename 雇员名, sal*12 全年工资 from emp;
注意：别名中有特殊字符或者区分大小写，必须加双引号""
连接符||
当执行查询操作时，为了显示更有意义的结果值，有时需要将多个字符串连接起来，连接字符串可以用||操作符
或者concat函数
把列与列，列与字符串连接在一起
用||表示。
可以用来合成列
select ename || '的岗位是' || job as 员工的职位信息描述 from emp;
字符串
字符串可以是select 列表中的字符，数字，日期。
日期和字符只能在单引号中出现。
每当返回一行时，字符串被输出一次
当在where子句中使用数字值时，即可用直接引用数字值，也可以用单引号引住数字值
select  * from emp where depno = 20;
当where子句中使用字符值，必须给字符值加上单引号。字符值是区分大小写的。
select * from emp where job = 'MANAGER';
当where子句使用日期值时，必须给日期值加上单引号。另外，日期值必须符合日期语言和显示格式。
select * from emp where hiredate = '02-4月-81';
where 子句比较运算符
= > >= < <= <> 或者 !=
select * from emp where sal > 1000 and sal < 3000;
select * from emp where sal < 1000 or sal > 3000;
范围查询between...and
between..and 用于指定特定范围的条件。
两值之间包含边界
between 较小值 and 较大值
select empno, ename, sal from emp where sal between 1500 and 3000;
等价于
select empno, ename, sal from emp where sal >= 1500 and sal <= 3000;
范围查询in
in执行列表匹配的操作
列或着表达式结果匹配列表中的任意一个值
in(值1， [值2, 值N])
select empno, ename, job from emp where job in ('salesman', 'manager', 'clerk');
等价于
select empno, ename, job, from emp where job = 'salsman' or job = 'manager' or job = 'clerk';
模糊查询like
用like执行模糊查询
当执行模糊查询时，需要使用通配符%和_
通配符%：用于表示0个或者多个字符。
通配符_：用于表示单个字符。
select * from emp where ename like 'J%';
select * from emp where ename like '_AR%';
如果字符值本身就包含_和%字符，并且开发人员希望使用这两个字符执行模糊查询，那么必须使用escape选项和转义符实现
回避特殊符号的方法：使用转义符，如将[%]转移为[\%],[_]转为[\_].然后再加上[escape'\']即可
select * from emp where ename like 'G\_%' escape '\';

判断空值 is null
is null 操作符用于检测列或者表达式的结果是否为null ，如果为null,则返回true,否则返回false.
判断列或表达式的结果是否为空可以用is null 或者 is not null, 但是不能用 =null 或者 <>null 来判断
select empno, ename, sal, comm from emp where comm is null;
select empno, ename, sal, comm from emp where comm is not null;
逻辑运算符 and or not

select empno, ename, job from emp where job not in ('clerk', 'salesman', 'mamnager');
这三个逻辑操作符中，not 优先级最高，其次时and,or 优先级最低，如果想改变优先级次序，要使用括号
select empno, ename, job, sal from emp where (sal > 2000 or depno = 30) and job not in ('persindent', manager);
排序order by 子句
select * |column[,column...] from table [where condition] [order by column[asc | desc]];
当select语句包含多个子句(where, group by, having, order by)时，order by 必须是最后一条语句
select ename, sal, from emp order by sal asc;(默认排序)
如果排序列存在NULL行，那么NULL行会显示在最后面。（升序）
select ename, sal from emp order by sal desc;
如果排序行存在NULL行，那么NULL行会显示在最前面
使用列别名排序
select empno, ename, sal*12 年收入 from emp order by 年收入 desc;
多列排序
当执行排序操作时，不仅可以基于单列进行排序，也可以基于多列进行排序，当以多列进行排序时，首先按照第一列进行排序，当第一列
存在相同的数据时，以第二列进行排序，以此类推。
select empno, ename, deptno, sal from emp order by deptno asc, sal desc;
4-10 sql语句和sqlplus 语句的区别
/*sqlplus可以运行sql语句
但是工具中不能运行sqlplus语句*/
sql:不区分大小写，关键字不能缩写 如select 
create alter drop truncate 		ddl
select insert update delete		dml
grant revoke 					dcl
commit rollback savepoint		tcl
结束需要加;
sqlpius:命令也不区分大小写，关键字可以缩写 如connect - conn,结束可以不加;
desc, show, conn, col, password
sql语句更改用户密码:alter user 用户名 identified by 新密码;
sqlplus命令
password:该命令用于修改用户的口令
password [username],username用于指定用户名，注意，任何用户都可以使用该命令修改其自身口令
但是如果想要修改其他用户口令，则必须要以dba的身份登录(sys/system)

sql语句
select ename as "雇员名"，sal as "工资" from emp;
sqlplus命令
col[umn]该命令用于控制列的显示属性
column column_name heading new_name
col ename heading '雇员名'
col sal heading '工资'
select ename, sal from emp;
如果Oracle的客户端与服务器都在一个电脑上，用sqlplus工具，通过如下代码连接数据库的时候可以只
启动一个服务
连接数据库命令:conn sys/password as sysdba
需要启动的服务:OracleServiceORCL
Oracle的客户端与服务器端不在同一个电脑上，或者即使在同一个电脑上，但是出现了下面的情况，都需要启动监听服务的
>连接数据库的命令:connect sys/oracle @orcl as sysdba
>通过图形化客户端工具连接数据库服务器时，如SQL Developer,PLSQL Developer工具
>登录基于Web的企业管理器EM时
总之：涉及到网络监听的地方是必须启动监听服务的
此时启动的最基本的服务有两个
OracleOraDb11g_home1TNSListener
OracleServiceORCL
5-1 Oracle的单行函数
SQL函数是oracle数据库的内置函数，并可用于各种SQL语句。
SQL函数包括单行函数(输入一行，输出一行)和多行函数(输入多行，输出一行的函数)
>字符函数类型
字符函数的输入参数为字符，其返回值是字符类型或者数字类型
大小写控制函数:输入值为null输出值也为null
upper(char):该函数用于将字符串转换为大写格式
select * from emp where job = upper('salesman')
lower(char):该函数用于将字符串转换为小写格式
select * from emp where lower(job) = 'clerk';
initcap(char):该函数用于将字符串中的每个单词的首字母大写，其他字符小写
select empno, initcap(ename) from emp;
字符控制函数:
concat(str1, str2),该函数用于字符串的连接，str1和str2用于指定被连接的字符串
concat('hello', 'oracle') --hellooracle
substr(char, m[,n]), 该函数用于截取字符串，char指定源字符串，m用于指定从哪个位置开始截取，n用于
指定截取字符串的长度。如果m为0，则从首字符开始，如果m为负数，则从尾部开始。
subcat('hello', 1, 3) --hel
substr('hello', 0, 3) --hel
sbustr('hello', -1, 1) --o
length,该函数用于返回字符串的长度，字符串中的后缀空格也记作字符串的长度
length('oracle') --7
instr(char1, char2[,n[,m]]),该函数用于取得子串在字符串中的位置，char1用于指定源字符串，char2用于
指定字串，n用于指定起始搜索位置(默认值为1)，m用于指定字串的第m次出现的次数(默认值为1)
instr('hello oracle', 'oracle_') --7
instr('hello oracle hello oracle', 'oracle', 1, 2) --20
lpad(char1, n, char2):该函数用于在字符串的左端填充字符,char1用于指定源字符串，char2用于指定被填充
的字符，n用于指定填充后char1的总长度。
lpad('hello', 10, '#') --#####hello
rpad
rpad('hello', 10, #) --hello##### 
trim, 
replace(char, search_string[,replacement_string]):该函数用于替换字符串的子串内容。char用于指定源字符串
，search_string用于指定被替换的子串，replacement_string用于指定替换子串
replacr('hello oracle', 'oracle', 'world') --hello world
SQL>select ename || ':' || sal from emp;
SQL>select * from emp where substr(job, 1, 4) = 'SALE';
SQL>select * from emp where length(ename) = '6';
SQL>select instr('hello oracle', oracle) from dual;
SQL>select instr('hello oracle hello oracle', 5, 2) from dual;
SQL>select lpad(job, 9, '*') from emp;
SQL>select rpad(job, 9, '*') from emp;
SQL>select replace('hello oracle', 'orcle', 'world');
>数值函数--输入和返回值都是数字类型
round(n, [m])
该函数用于返回四舍五入的结果，其中n可以是任意数字,m必须是整数
eg:round(25.365) --25
round(25.368,2) --25.37
round(25.368,-1) --30 小数点前一位
trunc(n, [m])该函数用于截取数字，其中n可以是任意数字，m必须是整数
eg:trunc(25.328) --25 截取小数点部分
trunc(25.328, 2) --25.32 截取小数点后2位
trunc(25.328, -1) --20 截取小数点前的第一位
mod(m, n)求模(求余数)该函数用于取得两个数字相除后的余数。如果数字n为0,则返回结果为m
eg:mod(25, 6) --1
mod(25, 0) --25
>日期函数
用于处理日期时间类型的函数
sysdate
用于返回系统当前日期
select sysdate - 1 昨天， sysdate 今天 from dual;
months_between
用于返回日期d1和d2之间相差的月数，d1大于d2结果为正数，否则为负数。
select months_between(sysdate, hiredate) from emp;
select round(months_betweem(sysdate, hiredate)/12)from emp;
add_months(d, n)该函数用于返回特定日期时间之后或者之前的月份所对应的日期。(求出若干月之后的日期)
d 用于指定日期时间，n可以是任意整数。
select ename, add_month(hiredate, 30*12) from emp;
next_day(d, char)该函数用于返回特定日期后的第一个工作日所对应的日期。d 用于这顶日期时间值，char用于指定工作日
注意:当使用该函数时，工作日必须与日期语言匹配，假如日期语言为american，那么周一对应于monday；加入日期语言为
简体中文，那么周一对应于"星期一"
select sysdate,next_day(sysdate, ‘星期一’)from dual;
last_day(d):该函数用于返回指定日期所在月份的最后一天
select sysdate, last_day(sysdate) from dual;
select empno, ename, hiredate from emp where hiredate = last_day(hiredate);
round(d, [,fmt]):该函数用于返回日期时间的四舍五入的结果。d用于指定日期的时间值，fmt用于指定四舍五入的方式
如果设置fmt为year，则7月1日为分界线，如果设置fmt为month,则16为分界线。
eg:系统时间是'20-7月-17'
round(sysdate,'year') --01-1月-18
round(sysdate, 'month') --01-8月-17
trunc(d,[,fmt]):该函数用于截断日期时间数据。d用于指定日期的时间值，fmt用于指定截断日期时间的方法,
如果设置为fmt为year, 则结果为本年度的1月1日，如果设置fmt为month,则结果为本月1日
trunc(sysdate,'year')
trunc(sysdate,'month')
>转换函数 用于将一种数据类型转换为另一种数据类型
Oracle可以隐式的进行数据类型转换
源数据类型					目标数据类型
varchar2/char				number
varchar2/char				date
number						varchar2
date						varchar2
to_date(char [,fmt[, 'nlsparams']])该函数用于将字符串转换我i日期类型的数据
char用于匹配日期数据的字符串，fmt用于指定日期格式模行，'nlsparams'用于指定日期语言。
select ename, hiredate from emp where hiredate > to_date('1981-12-31', 'YYYY-MM-DD');
to_char(d [, fmt[, 'nlsparams']])将日期类型转换为字符类型
d用于指定日期值，fmt用于指定日期格式模型'nlsparams'用于指定日期显示语言(格式:'nls_date_language = language')
默认的日期格式为DD-MON-RR
select to_char(hiredate, 'dd-mon-rr', 'nls_date_language = american') from emp;
注意:当在格式模型中增加字符值时，必须用双引号引住字符值。
select to_char(hiredate, 'YYYY-MM-DD') from emp
select to_char(hiredate, 'yyyy"年"mm"月"dd"日")from emp;
to_char(n [, fmt])将数值类型转换为字符类型
n用来指定数值， fmt用于指定数字格式的模式，格式模式，常用的元素如下:
9：显示数字，并且会忽略前导0
0：显示数字，如果位数不足，则用0补齐。
.:在指定位置显示小数点
,:在指定位置显示逗号
$:在数字前加美元符号
L：在数字前面加本地货币符号
to_number(n,[,fmt])该函数可以将包含数字的字符串转换成数值类型
n是包含数字的字符串，fmt用于指定数字格式模型
select ename, sal from emp where sal>to_number('￥2000，'L99999'')
>通用函数此类函数适用于任何数据类型，同时也适用于空值
nvl(expr1, expr2)该函数用于处理NULL,如果expr1是null,则返回expr2，如果expr1不是null,则返回expr1.
select ename, sal, comm, sal+nvl(comm, 0) from emp;	
select ename, sal, comm, sal+comm from emp;
在oracle9i之前，处理null只能使用nvl.
但从oracle9i以后，nvl或者nvl2都可以处理null
nvl2(expr1, expr2, expr3)该函数用于处理NULL
如果expr1不是null,则返回expr2,如果expr1是null,则返回expr3.
select ename, sal, comm, nvl2(comm, sal+comm, sal) from emp;
nullif(expr1, expr2)该函数用于比较表达式exper1和expr2,如果二者相等，则返回null,否则返回expr1。
select empno, ename, hiredate, nullif(hiredate, trunc(sysdate, 'month')) from emp;
coalesce(expr1[,expr2][,....])该函数用于返回表达式列表中的第一个not null 表达式的结果
select ename, sal, comm, coalesce(sal+comm, sal)from emp;
5-6条件表达式
case表达式
case expr
	when comparison_expr1 then retrun_expr1
	[when comparision_expr2 then return_expr2]
	........
	when comparison_exprn then return_exprn
	else else_expr]
end;
select empno, ename,
case job
when 'CLERK' then '办事员'
when 'SALESMAN' then '销售'
when 'MANAGER' then '经理'
when 'ANALYST' then '分析员'
end
from emp;
decode函数
decode(col | expression, search1, result1,
						[,search2, result2,...,]
						[,default])
decode 函数和case表达式都可以用于if-then-else 逻辑判断
select empno, ename, job,decode(job, 'clerk', '办事员'，'salesman', '销售'，'总裁') from emp;
select empno, ename, sal,
case when sal<2000 then '低'
when sal < 5000 then '中'
else '高'
end
from emp;
单行函数可以嵌套
嵌套函数的执行顺序是由内到外的
需求分析1
1>参照雇员信息表，想显示距聘用日期3个月后的下一星期一的日期，且日期格式为2017-01-06
分析
距聘用日期3个月后
add_months(hiredate,3)
下一星期一
next_day(add_months(hiredate, 3), '星期一')
且日期格式如下2017-01-06
to_char(next_day(add_months(hiredate,3),'星期一')，'YYYY-MM-DD')
需求分析2
2>参照雇员信息表，显示雇员日新斌四舍五入到2为小数的结果，然后对薪资格式以'￥1,182.19'这样的例子进行格式化
分析
雇员日新并四舍五入到2俄日小数的结果
round(sal/30, 2)
对薪资格式以'￥1,182.19'这样的例子进行格式化
to_char(round(sal/30, 2),'L9,999.99')
6-1 Oracle分组函数(多行函数):作用于一组数据，并对一组数据返回一个值
在关系数据库中，使用数据分组可以取得表数据的汇总信息。数据分组是通过分组函数,group by 以及having等子句共同实现的

avg:
select avg(sal) from emp;
sum:
min:
max:
count：
select count(*) from emp; --全部
select count(empno) from emp; --忽略空值
select count(distinct empno) from emp; --去除重复记录
wm_concat：该函数可以让查询结果行转列，可以把列值以','号分隔起来，并显示成一行。
select wm_conncat(ename) from emp;
分组函数与空值
使用分组函数有个重要的问题就是空值问题
eg:
求员工的平均工资
求员工的平均补助
>分组函数会自动忽略空值
>nvl函数使分组函数无法忽略空值
select count(nvl(comm,0))from emp;

6-2 Oracle的分组函数-group by
group by 子句的作用:可以将表中的数据分成若干组
group by 子句的语法:
select [column,] group function(column),...
from table
[where condition]
[group by group_by_expression]
[having group_condition]
[order by column];
eg:
select depno, avg(sal) from emp group by depno;
select列表中的列必须包含在group by 组函数列表中
eg:select depno, avg(sal) from emp  ERR!!!
select depno, job, avg(sal) from emp group by depno, job;
select avg(sal) from emp group by depno;--包含在group by 中的列，不必包含在select 列表中。
select deptno, wm_concat(ename) from emp group by depno;
6-3 Oracle的分组函数--having
作用:用于对分组后的结果进行过滤
eg:求平均工资大于2500的部门，要求显示：部门号，平均工资
select deptno, avg(sal) from emp group by deptno having avg(sal) > 2500;
注意：不能在where子句中使用分组函数，可以在having子句中使用组函数。
select deptno, avg(sal) from emp where avg(sal) > 2500 group by deptno;  ERR!!!
如果条件中没有组函数，正常使用where 语句就可以
eg:
select deptno, avg(sal) from emp where deptno = 10 group by deptno;
where 使得分组记录大大降低，从而提高效率
从SQL优化角度看，尽量使用where 子句。先过滤后分组。
分组函数的嵌套--必须使用group by 子句
select mac(avg(sal)) from emp group by deptno;
7-1 笛卡尔集
笛卡尔集是集合的一种，假设A和B都是集合，A和B的笛卡尔积用A*B来表示，A*B所形成的集合叫笛卡尔集
列数相加--行数相乘
为了避免笛卡尔积，可以在where子句中加入有效的连接条件
连接条件至少有n-1个，n代表表的个数
在表中有相同列时，在列名之前加上表名前缀。
Oracle的四种连接查询
>等值连接
等值连接是指使用等值比较符(=)指定连接条件的查询
select empno, ename, job, dname from emp, dept where emp.deptno = dept.no;
使用表名前缀在多个表中区分相同的列，提高执行效率
使用表的别名，可以简化连接查询并提高查询性能
select e.empno, e.ename, e.job, d.dnamefrom emp e, dept d where e.deptno = d.deptno;
当连接查询中，当有多个连接条件时，使用and指定其他条件。
select e.empno, e.ename, e.job, d.dnamefrom emp e, dept d where e.deptno = d.deptno and d.depno = 10;
>非等值连接
不等值连接是指使用除等值比较符之外的其他比较操作执行连接查询
select e.empno, e.sal, s.grade from emp e, salgrade s where e.sal between losal and hisal;
>自连接
自连接的实质是:将同一张表看成是多张表
select e.ename, m.ename from emp e, emp m where e.mgr = m.empno;
>外连接
外连接是标准连接的扩展，它不仅会返回满足条件的所有记录，而且还会返回不满足条件的部分记录
select d.deptno, d.dname, count(e.empno) from dept d, emp e where d.deptno =  e.deptno group by d.depno, d.dname;
部门标号为40的部门，员工数为0，没有显示出来
外联接语法
外连接是使用(+)操作来完成的。
右(外)连接:
select table.column, table2.column
from table1, table2
where table1.column(+) = table2.column;
返回的是等号右边表的全部记录(包括不满足条件的记录)，返回等号左边满足条件的记录
左(外)连接
select table1.column, table2.column
from table1, table2
where table1.column = table2.column(+)
返回的是等号左边表的全部记录
SQL：1999标准语法连接查询
为了简化查询，使得查询更加直观，更容易编写，SQL：1999标准为连接查询提供了新语法，
select table1.cloumn_name, table2.column_name from table1
[cross join table2] | [natural join table2] |
[join table2 usign(column_name)] |
[join table2 on (table.column_name = table2.column_name)] |
[left | right | full outer join table2 on (table1.column_name = table2.column_name)];
交叉连接cross join(了解)
返回笛卡尔集得操作
select d.dname, e.ename, d.deptno, e.deptno from dept d, emp e;
corss join 连接也用于生成两张表得笛卡尔集(叉集)
select d.dname, e.ename, d.deptno, e.deptno from dept d cross join emp e;
自然连接natural join
自然连接是一种特殊得等价连接，它将表中具有相同名称的列进行记录匹配。自然连接不必指定任何同等连接条件.
select table1.column_name, table2.column_name from table1 natural jion table2;
内连接 [inner] jion
返回两个表中相匹配的数据（只返回满足条件的数据），等值连接，非等值连接，自然连接都属于内连接外连接
用using子句建立相等连接
select e.name, e.sal, d.dname, from dept d [inner]jion emp e using(deptno);
用on子句建立相等连接
select e.ename, e.sal, d.dname from dept d jion emp e on deptno = d.deptno;
左（外）连接left [outer] jion
左外连接用于返回满足连接条件的数据，以及不满足连接条件的左表的其他数据(即：左表的全部记录，右表满足条件的记录)
在SQL:1999标准中，左连接是通过left[outer]jion 选项来实现的
select e.ename, e.sal, d.dname, from dept d left jion emp.e on e.deptno = d.deptno;
右（外）连接right [outer] jion
完全（外）连接full [outer] join
完全连接用于返回满足连接条件的数据，以及不满足连接条件的左边表和右边表的其他数据（即：左表和右表的全部记录）
select e.ename, e.sal, d.dname from dept d full jion emp e on e.deptno = d.deptno;
Orcle的set运算符
集合操作符专门合并多条select 语句的结果，包括4种：
union/union all 并集 
{1,2,3} union {3,4} = {1,2,3,4} 
{1,2,3} union all {3,4} = {1,2,3,3,4}
union 操作符用于取得两个结果集的并集，当使用该操作符时，会自动去掉结果集中的重复行，并且会以第一列的结果进行升序排列。
create table emp01 as select * from emp where deptno in(10, 20);
create table emp02 as select * from emp where deptno in (20,30);
select deptno, empno, ename from emp01 
union
select deptno, empno, ename from emo02;  
union all 操作符用于取得两个结果集的并集，但与union操作符不同，该操作符不会取消重复行，并且不会对结果集数据进行排序。
intersect 交集
intersect操作符用于取得两个结果集的交集，当使用该操作符时，只会显示同时存在与两个结果集中的数据，并且会以第一列的结果进行升序排列。
minus 差集
minus操作符用于取得两个结果集的差集，当使用该操作符时，只会显示在第一个结果集中存在，第二个结果集中不存在的数据。并且会以第一列的结果集进行升序排列。
控制结果排序
当使用集合操作符union，intersect和minus时，默认情况下会自动基于第一列进行升序排序；而当使用集合操作符union all 时，不会进行排序，为了控制结果的排序顺序，可以使用order by 子句。
select depno, emni, ename from emp01 
union all 
select depno, empno, ename from emp02 
order by 1;
使用set 操作符的注意事项
在select列表中的列名和表达式在数量和数据类型上要相对应
8-1 Oracle的子查询
子查询是指嵌套在其他sql语句中的select 语句，也称嵌套查询。
select * from emp where job = (select job from emp where ename = 'SMITH')；
--ddl语句中的子查询
create table empnew as select * from emp;
子查询的语法
select select_list
from table
where expr operator
			（select select_list
			from table）;
可以在子查询的位置：where, select, having, from 
--
select deptno, dname, loc,(select count(empno) from emp where emp.deptno = dept.deptno) cnt from dept;
select deptno, avg(sal) from emp group by deptno having avg(sal) > (select max(sal) from emp where deptno = '30')
select ename, job, sal from emp,(select deptno, avg(sal) from emp group by deptno) avgsal where emp.deptno = dept.deptno and sal > avgsal;  
8-2 Oracle 的主查询和子查询
select * from where job = (select job from emp where empno  = 7521) and sal > (select sal from emp where empno = 7934);
一般先执行子查询， 再执行主查询，但相关子查询例外。
select epno, ename, sal from emp where sal < (select avg(sal) from emp);
相关子查询
当子查询需要引用主查询的列表时，Oracle会执行相关子查询。
相关子查询是先执行主查询，再执行子查询。
select ename, sal, deptno from emp e where sal > (select avg(sal) from emp where deptno = e.deptno);
主查询和子查询可以不是同一张表
select * from emp where deptno = (select deptno from dept where dname = 'accounting');
select e.* from emp e, dept d where e.deptno = d.deptno and d.dname = 'accounting';
8-3 Oracle 的单行子查询
单行子查询
只返回一行数据的子查询语句，使用单行比较操作符
=, >=, <>, <=, >, <,
select ename, sal, deptno from emp where deptno(select deptno from emp where ename='james') and ename <> 'james'
select ename, job, sal from emp where sal >= (select avg(sal) from emp);
select * from emp where deptno <> (select deptno from dept where dname = 'saves');
非法使用单行子查询
select ename, job, sal from emp where sal = (select max(sal) from emp group by deptno)
多行子查询
多行子查询是指返回多行数据的子查询语句
使用多行比较操作符
in, 等于列表中的任何一个
select * from emp where deptno in (select deptno from dept where loc = 'new york' or lock = 'chicago');
all,和子查询返回的所有值进行比较 //不能单独使用
select ename, sal, depno from emp where sal > all(select sal from emp where deptno = 30)
select ename, sal, deptno from emp where sal > (select max(sal) from emp where deptno = 30)
any，和子查询返回的任意值进行比较//不能单独使用
select ename , sal, deptno from emp where sal > any(select sal from emp where depno = 10);
8-5 Oracle子查询需要注意的问题
不可以在group by子句中使用子查询
select avg(sal) from emp group by (select deptno from emp)
在top_n分析问题中，需对子查询排序。
eg:显示员工信息表中工资最高的前五名员工
select rownum, empno, ename, sal from (select * from emp order by sal desc);
select empno, ename, sal from emp where rownum <= 5 order by sal desc;
select rownum, empno, ename, sal from (select * from emp order by sal desc) where rownum <= 5;
单行子查询和多行子查询中的空值问题
单行子查询的空值问题
select ename, job from emp where job = (select job from emp where ename = 'ruby');
如果子查询返回了一个空值，则主查询将不会查询到任何结果
多行子查询的空值问题
select * from emp where empno not in (select mgr from emp);
如果子查询返回了一个空值，则主查询将不会查询到任何结果
9-Oracle 数据对象--视图
常见的数据库对象
表		基本的数据存储集合，由行和列组成
视图	从表中抽出的逻辑相关的数据集合
序列	提供有规律的数值
索引	提高查询的效率
同义词	给对象起的别名
视图是一个虚拟的表
视图建立在已有表的基础上，视图赖以建立的这些表车位基表
向视图提供数据内容的语句为select语句
1.安全原因，限制数据访问
2.视图可以使复杂的查询易于理解和使用
视图的分类
简单视图
基于单个表创建	示例一：建立用于查询员工号，姓名，工资的视图
system: grant create view to scott;
create view emp_view
as
select empno, ename, sal from emp;

create view emp_view2(员工号，姓名，工资)
as 
select empno, ename, sal from emp;
复杂视图
连接视图
示例二：建立用于获得部门号为10的部门号，部门名称以及员工信息
create view dept_emp_view
as 
select d.deptno,d.dname, e.empno, e.job
from dept d, emp e
where d.deptno = e.deptno and d.deptno = 10;
select * from dept_emp_view
只读视图
示例三：建立查看10号部门员工信息的视图
create view emp_view
as
select * from emp where deptno = 10
with read only; 
创建视图的语法格式
create [or replace] view view[(alias[,alias]...)]
as subquery
[with check option [constraint constraint]]
[with read only]
9-2 Oracle视图的修改与删除
视图上的DML操作
查询视图
select * from empnew_view;
添加数据-insert
insert into empnew_view (empno, ename, sal) values(888, 'layna', 6666);
修改数据 update
update empnew_view set sal = sal + 100 where empno = 888
删除数据 delete
delete from empnew_view where empno = 8888;
注意：
针对视图的更新操作（insert, update, delete）实际改变的是基表中的数据
在创建视图时定义check约束(with check option)
create view empnew_view
as 
select * from empnew where deptno = 20
with check option constriant chk_view
当update/insert的信息，不满足deptno = 20 则违反check约束。
修改视图
使用create or replace view 子句修改视图
create or replace view emp_view 
as 
select * from emp where job = 'salesman';
删除视图
当时图不在需要时，用户可以执行drop view 语句删除视图
drop view view ;
9-3复杂视图
复杂视图是指包含函数，表达式或者分组数据的视图，它主要用于执行查询操作
注意：当定义复杂视图时，必须要为函数或者表达式定义列别名。
实例：
创建用于获得每个岗位平均工资，工资总和，最高工资和最低工资的视图。
create view job_view(job, avgsal, sumsal, maxsal,minsal)
as
select job, avg(sal), sum(sal), max(sal), min(sal)
from emp
group by job;
复杂视图上执行DML操作的原则
delete操作的原则：
视图中包含以下元素之一不能执行delete操作：
group by 子句
分组函数
distinct 关键字
rownum伪列
update操作原则：
视图中包含以下元素之一不能执行update操作：
group by 子句
分组函数
distinct 关键字
rownum伪列
使用表达式定义的列
insert操作原则
视图中包含以下元素之一不能执行insert操作：
group by 子句
分组函数
distinct 关键字
rownum伪列
使用表达式定义的列
视图上没有包含基表的not null 列




















