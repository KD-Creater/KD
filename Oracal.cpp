1-4
ƽ����˵��Oracle��Oracle���ݿ�ָ����Oracle���ݿ����ϵͳ
��ô���������ֹ��ɣ���Oracle���ݿ��Oracleʵ��
1-5 SQL Plus ��������
desc
col[umn]
pass[word]
connect username/password
show user
host<dos ����>  SQL> host mkdir d:\OracleTest;
spool:������¼���ļ� SQL> spool d:\OracleTest\test.txt;
					 SQL> select * from tablename;
					 SQL> spool off��
clear screen:����
start:ִ�нű�		SQL>start d:\test.sql;
show error:��ʾ������Ϣ
exit:�˳�
2-1 ϵͳ�û���¼Oracle
Oracle Ĭ�ϵ�ϵͳ�û�:sys ֻ����ϵͳ����Ա����ϵͳ����������¼ 
					  system
					  sysman��Oracle���ݿ�������EM������û�
					  scott��Oracle�ṩ��ʾ���û���������һЩ����ѧ��ѧϰ���������ݱ�
					  (emp,dept,salgrade,bonus)
Oracle�û���¼
{<username>[/password][@<connect_identifier>]} | [as{sysdba | sysoper}]
1>username/password ָ�����ݿ��˻����Ϳ���
2>connect_identifier ���ݿ����ӵ����ӱ�ʶ��(��������)�����û�����ӱ�ʶ����SQL*Plus���ӵ�Ĭ�����ݿ�
3>sysdba:���ݿ����ԱȨ��	sysoper:���ݿ����ԱȨ��

����scott�û�
���û�����: alter user username account unlock;(��sys�û�Ȩ�޵�¼)
SQL>alter user scott account unlock;
SQL>conn scott/tiger;
SQL>select table_name from user_tables;(�鿴��ǰ״̬�����еı���Ϣ)

2-2 ��ռ�
������ռ�
create[temporary]tablespace tablespace_name tempfile|datafile 'xxx.dbf' size xx;
SQL>create tablespace test1_tablespace datafile 'test1file.dbf' size 10m;
SQL>create temporary tablespace temptest1_tablespace tempfile 'tempfile1.dbf' size 10m
SQL>select file_name from dba_data_files where tablespace_name = 'TEST1_TABLESPACE';�鿴��ռ��λ��
SQL>select file_name from dba_temp_files where tabelspace_name = 'TEMPTEST1_TABLESPACE';�鿴��ʱ��ռ��λ��

2-3 �����û�
create user <user_name> identified by <password> default <default tablespace>
temporary tablespace <temporary tablespace>;
select username from dba_users; (�鿴ϵͳ���е��û���)
���������û���Ȩ
grant Ȩ��to �û���
SQL>grant connect to yan;(���û�yan�������ӵ�Ȩ��)
�����û�
1>�����û�
connect �û���/����
2>��������
alter user �û��� identified by ������
>3��ϣ��ĳ�û���¼�����ֲ�ɾ�����û������Խ��û�����
alter user �û��� account lock;
4>ɾ���û�
drop user �û��� cascade //����cascade���û���ͬ�����Ķ���ȫ��ɾ��

2-4 ��ɫ
Oracle ��ɫ��role������һ��Ȩ�ޣ�����˵��Ȩ�޵ļ��ϣ�
�û����Ը���ɫ����ָ����Ȩ�ޣ�Ȼ�����ɫ������Ӧ���û�
3�ֱ�׼Ȩ��
1>connect(���ӽ�ɫ)
ӵ��connectȨ�޵��û�ֻ���Ե�¼oracle,�����Դ���ʵ�壬�����Դ������ݿ�ṹ
2>resource(��Դ��ɫ)
ӵ��resourceȨ�޵��û�ֻ���Դ���ʵ�壬�����Դ������ݿ�ṹ
3>dba�����ݿ����Ա��ɫ��
ӵ��ȫ����Ȩ����ϵͳ���Ȩ�ޣ�ֻ��DBA�ſ��Դ������ݿ�ṹ
������ͨ�û�������connect,resourceȨ��
����DBA�����û�������DBAȨ��
SQL>conn  as/sysdba		
SQL>create user user01 identified by 1	//��ָ����ռ�Ĭ��ʹ��ϵͳ��ռ䣬��������������������ϵͳ��ռ䱻մ��������崻�
SQL>grant connect to user01
SQL>grant resource to user01
SQL>conn user01/1
SQL>create table test(id number, name varchar2(200));
SQL>conn sys/1 as sysdba
SQL>grant dba to user01
SQL>create user user02 identified by 1
������ɫ
create role ��ɫ��
SQL>create role manager
Ϊ��ɫ����Ȩ��
grant Ȩ�� to ��ɫ
SQL>grant create table,create view to manager
����ɫ�����û�
grant ��ɫ to �û�
SQL>grant manager to user01 ,user02;
�ջ�Ȩ��
SQL>revoke manager from user 02;
ɾ����ɫ
SQL>drop role manager
2-5�û���Ȩ�޹���
Ȩ��ָ����ִ���ض�������߷������ݿ�����Ȩ��
Ȩ�޵ķ���
ϵͳȨ�ޣ������û�ִ���ض������ݿ⶯�����紴������������������ʵ����
����ʵ�壩Ȩ�ޣ������û�����һЩ�ض��Ķ������ȡ��ͼ������ĳЩ�У�ִ�д洢���̵ȡ�
�鿴Oracle ������ϵͳȨ��
SQL>select * from system_privilege_map
����ϵͳȨ�޵��﷨��ʽ
grant privilege[,pribilege...] to user [,user|role,public...]
SQL>grant create table, create sequence to manager;
SQL>grant manager to user01,user02;
����ϵͳȨ�޵��﷨��ʽ
revoke{privilege | role} from {user_name | role_name | public}
SQL>revoke manager from user01;
SQL>revoke create table,create sequence from manager;
����Ȩ��
��ѯOracle ���еĶ���Ȩ��
SQL>select * from table_privilege_map;
���õĶ���Ȩ���磺select ,update, insert, delete, all ��//allΪ����Ȩ��
�������Ȩ�޵��﷨��ʽ
grant object_priv | all [(columns) on object to {user|role|public}]
SQL>grant select, update, insert on scott.emp to manager2;
SQL>grant manager2 to user03;
SQL>grant all on scott.emp to user04;
���ն���Ȩ�޵��﷨��ʽ
revoke{privilege[,privilege...] | all} on object from {user[,user...] | role public}
SQL>revoke all on scott.emp frim user04;
2-6 ��ռ����
��ص������ֵ�
1>dab_tablespaces
2>user_tablespaces
3>dba_users
4>user_users
SQL>select tablespace_name from dba_tablespaces;
SQL>select default_tablespace, temporary_tablespace from user_users where username = 'SYSTEM';
�����û�Ĭ�ϻ�����ʱ��ռ�
1>alter user username deflaut | temporary tablespace tablespace_name;
SQL>alter user user01 defalut tablespace test01_tablespace 
�޸ı�ռ��״̬
alter tablespace tablesapce_name online | offline | read only | read write  (=online);
���һ����ռ����ó��ѻ�״̬����ʾ�ñ�ռ���ʱ���÷��ʣ�������ɾ�������ó�����״̬��������ʹ�á�
Ĭ���ǿɶ���д״̬
���/ɾ�������ļ�
alter tablespace tablespce_name add datafile'filename.dbf' 
alter tablespace tablespace_name drop dataflie 'fliename.dbf';
SQL>alter tablespace test01_tablespace add datafile 'test02_dataflie.dbf' size 10m;
SQL>select file_name from dba_data_files where tablespace_name = 'test01_tablespace';
����ɾ����ռ��еĵ�һ�������������ļ��������Ҫɾ��������Ҫ��������ռ�ɾ����
ɾ����ռ�
drop tablespace tablespace_name[includind contents];
���ɾ��ʱֻ�뵥����ɾ����ռ䣬����ɾ�������ļ��Ļ�������:drop tablespace tablespace_name;
������������ļ�һ��ɾ��ʱ��Ҫ��� including contents
3-2
DDL(data definition language)���ݶ�������
-create table:������
-create index:��������
-drop table
-drop index
-truncate:ɾ�����е�������
-alter table:���ı�ṹ�����ӣ����ģ�ɾ����
-alter table add constraint:�����еı�������Լ��
DML(data maniulation language)���ݲ�������
-insert
-update
-delete
-select
DCL(data control language)���ݿ�������
-grant
-revoke
-lock
TCL(transation control language)�����������
-commit:�ύ������
-rollback:���������
-savepoint:���ñ����
3-3 ������
create table table_name(
	colum_name datetype
) 
��������
�ַ�����:
char:��ʾ�̶����ȵ��ַ������г��ȿ���ʱ1��2000���ֽ�
varchar2:��ʾ�ɱ䳤�ȵ��ַ�������󳤶�Ϊ4000�ֽ�
number[(p[,s])]:p��ʾ���ȣ�s��ʾС�����λ�������Դ洢����������������ֵ���ͣ���߾���Ϊ38λ
eg:number(5,0)�����Դ洢��λ����
	number(5,2)���ɴ洢999.99�ĸ�����
date:��������
lob:
1>clob��character lob:���ܹ��洢�����ַ�����
2>blob��binary lob:�����Դ洢�ϴ�Ķ����ƶ�����ͼ�Σ���Ƶ�����������ļ���
3-4 Լ��
Լ����oracle�ṩ���Զ��������ݿ������Ե�һ�ַ�������ͨ�������ֶ��е����ݣ���¼���ݺͱ�֮���������
��֤���ݵ������ԡ�
������Լ�����﷨Ϊ
[constraint constraint_name]<Լ������>--Լ����ָ������ʱ��ϵͳ�����һ�����ơ�
oracle �е�Լ��:
����Լ��(primary key constraint)
primary key Լ�����ڶ���������������Ψһȷ������ÿһ����¼�ı�ʶ������ֵ����Ϊ�գ�Ҳ�����ظ����Դ���ȷ��ʵ��������ԡ�
����������ֻ����һ�����������ɶ���й��ɣ���primary key(ѧ�ţ���Ŀ���)��
�������Լ��:
������ʱ������Լ��
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20),
SQL>csex char(2),
SQL>caddr varchar2(50),
SQL>cbrith date��
SQL>cconstriant sid_pk primary key(sid)
);
�޸ı��������Լ��
alter table student add constraint sid_pk primary key (sid);
Ψһ��Լ��(unique constraint)
Ĭ��Լ��(defalut constraint)
�ǿ�Լ��(not null constriant)
���Լ��(check constriant)
�ⲿԼ��(foreign key constraint)
3-5 �ǿ�Լ��
not null Լ������ȷ���в���ΪNULL�����������not nullԼ������ô����������ʱ������Ϊ�����ṩ���ݣ�
����������ʱ�����ܽ���ֵ����ΪNULL��
�ǿ�Լ�����м�Լ��
�м�Լ��:
column [constraint constraint_name] constraint_type,
˵��:�м�Լ����������еĶ������
��Լ��:
[constraint constraint_name] constriant_type
˵��:��Լ�������м�һ�𣬶��ǵ�������ġ�
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) constraint nn_sex not null, --�м�Լ��
SQL>caddr varchar2(50),
SQL>cbrith date��
SQL>cconstriant sid_pk primary key(sid) --��Լ��
);
�޸ı����Լ���ĸ�ʽ�Ա�
1>�޸ı����Լ�����﷨��ʽ:
alter table table_name add [constraint constriant_name] constraint_type(column);
2>�����not null Լ��Ҫʹ��modify
alter table table_name modify (column datatype not null);
ɾ��Լ���ķ�ʽ
1>��Լ����Ч�����߼���
disable | enable constraint constraint_name
2>��Լ������ɾ��
drop constriant constraint_name
>ɾ������Լ���ĸ�ʽ��
drop primary key
>ɾ���ǿ�Լ���ķ�ʽ
alter table table_name modify column_name datatype null;
SQL>alter table student disable constrinat pk_sid;
SQL>alter table student drop constraint pk_sid;
SQL>alter table student drop primary key;
3-6 ΨһԼ��
Ψһ��Լ������ָ��һ�����߶���е����ֵ����Ψһ�ԣ��Է�ֹ�����������ظ���ֵ
ע��:
>ʹ��Ψһ��Լ����������Ϊ��ֵ
>һ�����п��������ж��Ψһ��Լ��
>���԰�Ψһ��Լ�������ڶ������
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) constraint nn_sex not null, --�м�Լ��
SQL>caddr varchar2(50),
SQL>cbrith date��
SQL>cconstriant sid_pk primary key(sid) --��Լ��
SQL>cardid varchar2(18),
SQL>email varchar2(50) unique,
constraint uk_cardid unique(cardid)
);
�޸ı�ʱ���Ψһ��Լ��
alter table student add constraint uk_cardid unique(cardid);
����Լ��
alter table student disable constraint uk_cardid;
ɾ��Լ��
alter table student drop constraint uk_cardid;
3-7 ���Լ��
���Լ���������л����������е�ֵ���ü������������������ֵ����֤���ݿ����ݵ������ԡ�
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) check(sex='��' or 'Ů'), --�м�Լ��
SQL>caddr varchar2(50),
SQL>cbrith date��
SQL>cconstriant sid_pk primary key(sid) --��Լ��
SQL>cardid varchar2(18),
SQL>email varchar2(50) unique,
SQL>constraint ck_sex check (sex='��' or 'Ů')��
)

alter table student add constraint ck_sex check(sex = '��' or 'Ů')��
alter table student disable constraint ck_sex;
alter table student drop constraint ck_sex;
3-8���Լ��
���Լ��(foreign key), 	�����ڽ����ͼ�ǿ������֮������ӵ�һ�л��߶��С����Լ����Ψһ�漰�������ϵ��Լ��
�������Լ�����﷨��ʽ(�����Ѵ��ڣ������ӱ�ʱ����)
create table �ӱ�(column_name datatype references ����(column_name) [on delete cascade],...);
constraint constraint_name foreign key (column_name) references ���� (column_name)[on delete cascade]
��������:
create table department(depid varchar2(20) primary key,
depname varchar2(30));
�����ӱ�
SQL>create table student(
SQL>csid number(8,0),
SQL>cname varchar2(20) not null,
SQL>csex char(2) constraint nn_sex not null, --�м�Լ��
SQL>caddr varchar2(50),
SQL>cbrith date��
SQL>depid varchar2(10) references department(depid);
SQL>constriant fk_depid foreign key(depid) references department(depid) on delete cascade --��Լ��
);
ע������
�������Լ��ʱ������ֶα�����������(��Ψһ��)
���ӱ���Ӧ�ֶα�����ͬһ��������
�ӱ�������ֶε�ֵ�������������е���Ӧ�ֶε�ֵ������ΪNULLֵ��
alter table student add constraint fk_depid foreign key(depid) references department(depid) on delete cascade; 
3-9 Oracle�ı����--�޸ĺ�ɾ����DDL
alter table ���� add  �������� ��������
SQL>alter table student add tel varchar2(20);
alter table ���� modify ���� ����������
SQL>alter table student modify tel number(20,0);
alter table ���� drop column ����
SQL>alter table student drop colum tel;
alter table ���� rename column ���� to ������
SQL>alter table student rename  column sex to gender;
rename ���� to �±���
SQL>rename student to studentinfo;
truncate table ����;
truncate table��������ɾ�����е�ȫ�����ݣ������ǰɱ�ɾ���������ַ�ʽҪ��delete��ʽɾ������Ҫ�죬
Ҳ�нضϱ�
drop table ����;ɾ����ṹ
3-10 Oracle�ı����--��ɾ�Ĳ� dml
insert into ����[��1,��2,...��n]values(ֵ1��ֵ2...,ֵn)
SQL>insert into student(sid,name,sex) values(2001001,'����','Ů');
SQL>insert into student(sid,name,sex,address,birhday)values(20010002,'wangwu','beijing',to_date('19820909','YYYYMMDD'))��
select * | column[����] from ����;
update table set column = value [,column = value,...] [where condition];
delete from table [where condition];
3-11 Oracle�ı����--����
ʲô������?
������Կ������ɶ����ݿ�����ɲ�����ɵ�һ����Ԫ����Щ����Ҫô����ɣ�Ҫô��ȡ�����Ӷ���֤��������
һ���Ե�Ҫ��
�������ɣ�
>һ�����߶���DML
>һ��DDL
>һ��DCL
DML�����Ҫʹ��commit �ύ�������ʹ��rollback�ع�����
DDL��DCL���Զ��ύ�����
ʹ�������ԭ�򣺱�֤���ݵİ�ȫ��Ч
��ִ���������(DML���)ʱ��Oracle���ڱ����õı��ϼӱ������Է�ֹ�����û��ı��ṹ��ͬʱ���ڱ�����
�����ϼ��������Է�ֹ���������ڶ�Ӧ����ִ��DML������
�ύ����commit��
ͨ��commit�������ύ���񣬵�ִ����commit���󣬻�ȷ������ı仯����������ɾ������㣬�ͷ���
��ʹ��commit����������������Ự�����Բ鵽����仯���µ����ݡ�
�ع�����(rollback)
rollbackֻ�ܶ�δ�ύ�����ݳ������Ѿ�commit���������޷������ģ���Ϊcommit֮���Ѿ��־û������ݿ��С�
�����(savepoint)
�������е�һ�㣬����ȡ���������񣬵���������ʱ�����Զ���ɾ������������������б���㣬��ִ��rollbackʱ
ͨ��ָ���������Ի��˵�ָ���ĵ㡣
���ñ���㣺savepoint a;
�ع���������rollback to a;
�ع�ȫ������rollback;
3-12 �����ֵ�
�����ֵ���Oracle����й����ݿ���Ϣ�ĵط�������;�������������ݵģ������ֵ���һ������ͼ�ṹ
���ݿ��еı��ǲ���ֱ�ӱ����ʵģ����ǿ��Է��������ֵ����ͼ
ͨ�������ֵ䣬ʹ�����˽����ݿ��ڲ�����Ϣ�����û��ڶ����ݿ��е����ݽ��в���ʱ�������ѾͿ��Է�������
�ֵ����鿴��ϸ����Ϣ
Oracle �г��õ������ֵ��Ϊ���࣬������ǰ׺��ͷ��
uesr_*
����ͼ�洢�˹��ڵ�ǰ�û���ӵ�еĶ������Ϣ�����������ڸ��û�ģʽ�µĶ���,
all_*
����ͼ�洢�˵�ǰ�û��ܹ����ʵĶ�����Ϣ����user_*��ȣ�all_*������Ҫӵ�иö���ֻҪ���з��ʸö��󣩵�Ȩ�޼��ɣ�,
dba_*
����ͼ�洢�����ݿ������ж������Ϣ����ǰ���ǵ�ǰ�û����з�����Щ���ݿ��Ȩ�ޣ�һ����˵������й���ԱȨ�ޣ�
Oracle ���õ������ֵ�
user_users			�����û�����Ϣ
user_tablespaces	
user_tables
user_views
user_sequences
user_constraints
user_triggers
user_source
4-1 Oracle�Ļ�����ѯ
select * | {[distinct] column | expression[alias],....} from table [where condition]

table ����ָ������
column ����ָ������
expression ���ʽ
alias ����ָ���еı���
condition ��ѯ����

�ų��ظ���
select distinct deptno,job from emp;
����������
������:��ָ��������Ϊ�������͵��У���date����
�����е�Ĭ�ϸ�ʽΪDD_MON_RR
RR:�����꣬����ֻȡ��ݵĺ���λ���֡�
�Լ���������ʾ���ڽ��
����Լ���������ʾ���ڽ������ô���Խ��Ự��nls_language ��������Ϊsimplified chinese
alter session set nls_language = 'simplified chinese';
�������������Ӣ����ʾ���ڽ������ô���Խ��Ự��nls_language��������Ϊamerican.
alter session set nls_language='american';
���ϣ������������ʾ��ʽ���������ض���ʽ��ʾ���ڽ������ô�������ûỰ��nls_date_format����
alter session set nls_date_format = 'YYYY/MM/DD';
���������+-*/�������������Ӧ�������ֺ����ڵ����ϡ�
select empno,ename,sal,sal*12 from emp;
select empno, ename, sal*12 + sal/2 from emp;
������������еĿ�ֵNULL ��ʾδֵ֪�����Ȳ��ǿո�Ҳ����0
���������ʽ����NULLʱ������ҲΪ��(NULL).
��ֵ:����������ʱ�����û��Ϊ�ض������ṩ���ݣ����Ҹ���û��Ĭ��ֵ����ô����ΪNULL
Ĭ��ֵ:�ڴ�����ʱ������ʹ��default�ؼ���Ϊ������Ĭ��ֵ���ڱ��в�������ʱ�����û��Ϊ�����ṩ���ݣ���ô����ʹ��Ĭ��ֵ/
create table student(sid number(8,0) primary key,name varchar2(10),sex char(2) default '��'��age number(2,0)default 20,address varchar2(50));
insert into student values(2001002,'wangwu',default,21,'beijing')
��ʹ���еı���
select empno,ename,sal*12 from emp;
ʹ���еı���
select empno "��Ա���", ename "��Ա��", sal*12 "ȫ�깤��" from emp; ����
select empno as "��Ա���", ename as "��Ա��", sal*12 as "ȫ�깤��" from emp; ����
select empno ��Ա���, ename ��Ա��, sal*12 ȫ�깤�� from emp;
ע�⣺�������������ַ��������ִ�Сд�������˫����""
���ӷ�||
��ִ�в�ѯ����ʱ��Ϊ����ʾ��������Ľ��ֵ����ʱ��Ҫ������ַ������������������ַ���������||������
����concat����
�������У������ַ���������һ��
��||��ʾ��
���������ϳ���
select ename || '�ĸ�λ��' || job as Ա����ְλ��Ϣ���� from emp;
�ַ���
�ַ���������select �б��е��ַ������֣����ڡ�
���ں��ַ�ֻ���ڵ������г��֡�
ÿ������һ��ʱ���ַ��������һ��
����where�Ӿ���ʹ������ֵʱ��������ֱ����������ֵ��Ҳ�����õ�������ס����ֵ
select  * from emp where depno = 20;
��where�Ӿ���ʹ���ַ�ֵ��������ַ�ֵ���ϵ����š��ַ�ֵ�����ִ�Сд�ġ�
select * from emp where job = 'MANAGER';
��where�Ӿ�ʹ������ֵʱ�����������ֵ���ϵ����š����⣬����ֵ��������������Ժ���ʾ��ʽ��
select * from emp where hiredate = '02-4��-81';
where �Ӿ�Ƚ������
= > >= < <= <> ���� !=
select * from emp where sal > 1000 and sal < 3000;
select * from emp where sal < 1000 or sal > 3000;
��Χ��ѯbetween...and
between..and ����ָ���ض���Χ��������
��ֵ֮������߽�
between ��Сֵ and �ϴ�ֵ
select empno, ename, sal from emp where sal between 1500 and 3000;
�ȼ���
select empno, ename, sal from emp where sal >= 1500 and sal <= 3000;
��Χ��ѯin
inִ���б�ƥ��Ĳ���
�л��ű��ʽ���ƥ���б��е�����һ��ֵ
in(ֵ1�� [ֵ2, ֵN])
select empno, ename, job from emp where job in ('salesman', 'manager', 'clerk');
�ȼ���
select empno, ename, job, from emp where job = 'salsman' or job = 'manager' or job = 'clerk';
ģ����ѯlike
��likeִ��ģ����ѯ
��ִ��ģ����ѯʱ����Ҫʹ��ͨ���%��_
ͨ���%�����ڱ�ʾ0�����߶���ַ���
ͨ���_�����ڱ�ʾ�����ַ���
select * from emp where ename like 'J%';
select * from emp where ename like '_AR%';
����ַ�ֵ����Ͱ���_��%�ַ������ҿ�����Աϣ��ʹ���������ַ�ִ��ģ����ѯ����ô����ʹ��escapeѡ���ת���ʵ��
�ر�������ŵķ�����ʹ��ת������罫[%]ת��Ϊ[\%],[_]תΪ[\_].Ȼ���ټ���[escape'\']����
select * from emp where ename like 'G\_%' escape '\';

�жϿ�ֵ is null
is null ���������ڼ���л��߱��ʽ�Ľ���Ƿ�Ϊnull �����Ϊnull,�򷵻�true,���򷵻�false.
�ж��л���ʽ�Ľ���Ƿ�Ϊ�տ�����is null ���� is not null, ���ǲ����� =null ���� <>null ���ж�
select empno, ename, sal, comm from emp where comm is null;
select empno, ename, sal, comm from emp where comm is not null;
�߼������ and or not

select empno, ename, job from emp where job not in ('clerk', 'salesman', 'mamnager');
�������߼��������У�not ���ȼ���ߣ����ʱand,or ���ȼ���ͣ������ı����ȼ�����Ҫʹ������
select empno, ename, job, sal from emp where (sal > 2000 or depno = 30) and job not in ('persindent', manager);
����order by �Ӿ�
select * |column[,column...] from table [where condition] [order by column[asc | desc]];
��select����������Ӿ�(where, group by, having, order by)ʱ��order by ���������һ�����
select ename, sal, from emp order by sal asc;(Ĭ������)
��������д���NULL�У���ôNULL�л���ʾ������档������
select ename, sal from emp order by sal desc;
��������д���NULL�У���ôNULL�л���ʾ����ǰ��
ʹ���б�������
select empno, ename, sal*12 ������ from emp order by ������ desc;
��������
��ִ���������ʱ���������Ի��ڵ��н�������Ҳ���Ի��ڶ��н������򣬵��Զ��н�������ʱ�����Ȱ��յ�һ�н������򣬵���һ��
������ͬ������ʱ���Եڶ��н��������Դ����ơ�
select empno, ename, deptno, sal from emp order by deptno asc, sal desc;
4-10 sql����sqlplus ��������
/*sqlplus��������sql���
���ǹ����в�������sqlplus���*/
sql:�����ִ�Сд���ؼ��ֲ�����д ��select 
create alter drop truncate 		ddl
select insert update delete		dml
grant revoke 					dcl
commit rollback savepoint		tcl
������Ҫ��;
sqlpius:����Ҳ�����ִ�Сд���ؼ��ֿ�����д ��connect - conn,�������Բ���;
desc, show, conn, col, password
sql�������û�����:alter user �û��� identified by ������;
sqlplus����
password:�����������޸��û��Ŀ���
password [username],username����ָ���û�����ע�⣬�κ��û�������ʹ�ø������޸����������
���������Ҫ�޸������û���������Ҫ��dba����ݵ�¼(sys/system)

sql���
select ename as "��Ա��"��sal as "����" from emp;
sqlplus����
col[umn]���������ڿ����е���ʾ����
column column_name heading new_name
col ename heading '��Ա��'
col sal heading '����'
select ename, sal from emp;
���Oracle�Ŀͻ��������������һ�������ϣ���sqlplus���ߣ�ͨ�����´����������ݿ��ʱ�����ֻ
����һ������
�������ݿ�����:conn sys/password as sysdba
��Ҫ�����ķ���:OracleServiceORCL
Oracle�Ŀͻ�����������˲���ͬһ�������ϣ����߼�ʹ��ͬһ�������ϣ����ǳ�������������������Ҫ�������������
>�������ݿ������:connect sys/oracle @orcl as sysdba
>ͨ��ͼ�λ��ͻ��˹����������ݿ������ʱ����SQL Developer,PLSQL Developer����
>��¼����Web����ҵ������EMʱ
��֮���漰����������ĵط��Ǳ����������������
��ʱ������������ķ���������
OracleOraDb11g_home1TNSListener
OracleServiceORCL
5-1 Oracle�ĵ��к���
SQL������oracle���ݿ�����ú������������ڸ���SQL��䡣
SQL�����������к���(����һ�У����һ��)�Ͷ��к���(������У����һ�еĺ���)
>�ַ���������
�ַ��������������Ϊ�ַ����䷵��ֵ���ַ����ͻ�����������
��Сд���ƺ���:����ֵΪnull���ֵҲΪnull
upper(char):�ú������ڽ��ַ���ת��Ϊ��д��ʽ
select * from emp where job = upper('salesman')
lower(char):�ú������ڽ��ַ���ת��ΪСд��ʽ
select * from emp where lower(job) = 'clerk';
initcap(char):�ú������ڽ��ַ����е�ÿ�����ʵ�����ĸ��д�������ַ�Сд
select empno, initcap(ename) from emp;
�ַ����ƺ���:
concat(str1, str2),�ú��������ַ��������ӣ�str1��str2����ָ�������ӵ��ַ���
concat('hello', 'oracle') --hellooracle
substr(char, m[,n]), �ú������ڽ�ȡ�ַ�����charָ��Դ�ַ�����m����ָ�����ĸ�λ�ÿ�ʼ��ȡ��n����
ָ����ȡ�ַ����ĳ��ȡ����mΪ0��������ַ���ʼ�����mΪ���������β����ʼ��
subcat('hello', 1, 3) --hel
substr('hello', 0, 3) --hel
sbustr('hello', -1, 1) --o
length,�ú������ڷ����ַ����ĳ��ȣ��ַ����еĺ�׺�ո�Ҳ�����ַ����ĳ���
length('oracle') --7
instr(char1, char2[,n[,m]]),�ú�������ȡ���Ӵ����ַ����е�λ�ã�char1����ָ��Դ�ַ�����char2����
ָ���ִ���n����ָ����ʼ����λ��(Ĭ��ֵΪ1)��m����ָ���ִ��ĵ�m�γ��ֵĴ���(Ĭ��ֵΪ1)
instr('hello oracle', 'oracle_') --7
instr('hello oracle hello oracle', 'oracle', 1, 2) --20
lpad(char1, n, char2):�ú����������ַ������������ַ�,char1����ָ��Դ�ַ�����char2����ָ�������
���ַ���n����ָ������char1���ܳ��ȡ�
lpad('hello', 10, '#') --#####hello
rpad
rpad('hello', 10, #) --hello##### 
trim, 
replace(char, search_string[,replacement_string]):�ú��������滻�ַ������Ӵ����ݡ�char����ָ��Դ�ַ���
��search_string����ָ�����滻���Ӵ���replacement_string����ָ���滻�Ӵ�
replacr('hello oracle', 'oracle', 'world') --hello world
SQL>select ename || ':' || sal from emp;
SQL>select * from emp where substr(job, 1, 4) = 'SALE';
SQL>select * from emp where length(ename) = '6';
SQL>select instr('hello oracle', oracle) from dual;
SQL>select instr('hello oracle hello oracle', 5, 2) from dual;
SQL>select lpad(job, 9, '*') from emp;
SQL>select rpad(job, 9, '*') from emp;
SQL>select replace('hello oracle', 'orcle', 'world');
>��ֵ����--����ͷ���ֵ������������
round(n, [m])
�ú������ڷ�����������Ľ��������n��������������,m����������
eg:round(25.365) --25
round(25.368,2) --25.37
round(25.368,-1) --30 С����ǰһλ
trunc(n, [m])�ú������ڽ�ȡ���֣�����n�������������֣�m����������
eg:trunc(25.328) --25 ��ȡС���㲿��
trunc(25.328, 2) --25.32 ��ȡС�����2λ
trunc(25.328, -1) --20 ��ȡС����ǰ�ĵ�һλ
mod(m, n)��ģ(������)�ú�������ȡ�����������������������������nΪ0,�򷵻ؽ��Ϊm
eg:mod(25, 6) --1
mod(25, 0) --25
>���ں���
���ڴ�������ʱ�����͵ĺ���
sysdate
���ڷ���ϵͳ��ǰ����
select sysdate - 1 ���죬 sysdate ���� from dual;
months_between
���ڷ�������d1��d2֮������������d1����d2���Ϊ����������Ϊ������
select months_between(sysdate, hiredate) from emp;
select round(months_betweem(sysdate, hiredate)/12)from emp;
add_months(d, n)�ú������ڷ����ض�����ʱ��֮�����֮ǰ���·�����Ӧ�����ڡ�(���������֮�������)
d ����ָ������ʱ�䣬n����������������
select ename, add_month(hiredate, 30*12) from emp;
next_day(d, char)�ú������ڷ����ض����ں�ĵ�һ������������Ӧ�����ڡ�d �����ⶥ����ʱ��ֵ��char����ָ��������
ע��:��ʹ�øú���ʱ�������ձ�������������ƥ�䣬������������Ϊamerican����ô��һ��Ӧ��monday��������������Ϊ
�������ģ���ô��һ��Ӧ��"����һ"
select sysdate,next_day(sysdate, ������һ��)from dual;
last_day(d):�ú������ڷ���ָ�����������·ݵ����һ��
select sysdate, last_day(sysdate) from dual;
select empno, ename, hiredate from emp where hiredate = last_day(hiredate);
round(d, [,fmt]):�ú������ڷ�������ʱ�����������Ľ����d����ָ�����ڵ�ʱ��ֵ��fmt����ָ����������ķ�ʽ
�������fmtΪyear����7��1��Ϊ�ֽ��ߣ��������fmtΪmonth,��16Ϊ�ֽ��ߡ�
eg:ϵͳʱ����'20-7��-17'
round(sysdate,'year') --01-1��-18
round(sysdate, 'month') --01-8��-17
trunc(d,[,fmt]):�ú������ڽض�����ʱ�����ݡ�d����ָ�����ڵ�ʱ��ֵ��fmt����ָ���ض�����ʱ��ķ���,
�������ΪfmtΪyear, ����Ϊ����ȵ�1��1�գ��������fmtΪmonth,����Ϊ����1��
trunc(sysdate,'year')
trunc(sysdate,'month')
>ת������ ���ڽ�һ����������ת��Ϊ��һ����������
Oracle������ʽ�Ľ�����������ת��
Դ��������					Ŀ����������
varchar2/char				number
varchar2/char				date
number						varchar2
date						varchar2
to_date(char [,fmt[, 'nlsparams']])�ú������ڽ��ַ���ת����i�������͵�����
char����ƥ���������ݵ��ַ�����fmt����ָ�����ڸ�ʽģ�У�'nlsparams'����ָ���������ԡ�
select ename, hiredate from emp where hiredate > to_date('1981-12-31', 'YYYY-MM-DD');
to_char(d [, fmt[, 'nlsparams']])����������ת��Ϊ�ַ�����
d����ָ������ֵ��fmt����ָ�����ڸ�ʽģ��'nlsparams'����ָ��������ʾ����(��ʽ:'nls_date_language = language')
Ĭ�ϵ����ڸ�ʽΪDD-MON-RR
select to_char(hiredate, 'dd-mon-rr', 'nls_date_language = american') from emp;
ע��:���ڸ�ʽģ���������ַ�ֵʱ��������˫������ס�ַ�ֵ��
select to_char(hiredate, 'YYYY-MM-DD') from emp
select to_char(hiredate, 'yyyy"��"mm"��"dd"��")from emp;
to_char(n [, fmt])����ֵ����ת��Ϊ�ַ�����
n����ָ����ֵ�� fmt����ָ�����ָ�ʽ��ģʽ����ʽģʽ�����õ�Ԫ������:
9����ʾ���֣����һ����ǰ��0
0����ʾ���֣����λ�����㣬����0���롣
.:��ָ��λ����ʾС����
,:��ָ��λ����ʾ����
$:������ǰ����Ԫ����
L��������ǰ��ӱ��ػ��ҷ���
to_number(n,[,fmt])�ú������Խ��������ֵ��ַ���ת������ֵ����
n�ǰ������ֵ��ַ�����fmt����ָ�����ָ�ʽģ��
select ename, sal from emp where sal>to_number('��2000��'L99999'')
>ͨ�ú������ຯ���������κ��������ͣ�ͬʱҲ�����ڿ�ֵ
nvl(expr1, expr2)�ú������ڴ���NULL,���expr1��null,�򷵻�expr2�����expr1����null,�򷵻�expr1.
select ename, sal, comm, sal+nvl(comm, 0) from emp;	
select ename, sal, comm, sal+comm from emp;
��oracle9i֮ǰ������nullֻ��ʹ��nvl.
����oracle9i�Ժ�nvl����nvl2�����Դ���null
nvl2(expr1, expr2, expr3)�ú������ڴ���NULL
���expr1����null,�򷵻�expr2,���expr1��null,�򷵻�expr3.
select ename, sal, comm, nvl2(comm, sal+comm, sal) from emp;
nullif(expr1, expr2)�ú������ڱȽϱ��ʽexper1��expr2,���������ȣ��򷵻�null,���򷵻�expr1��
select empno, ename, hiredate, nullif(hiredate, trunc(sysdate, 'month')) from emp;
coalesce(expr1[,expr2][,....])�ú������ڷ��ر��ʽ�б��еĵ�һ��not null ���ʽ�Ľ��
select ename, sal, comm, coalesce(sal+comm, sal)from emp;
5-6�������ʽ
case���ʽ
case expr
	when comparison_expr1 then retrun_expr1
	[when comparision_expr2 then return_expr2]
	........
	when comparison_exprn then return_exprn
	else else_expr]
end;
select empno, ename,
case job
when 'CLERK' then '����Ա'
when 'SALESMAN' then '����'
when 'MANAGER' then '����'
when 'ANALYST' then '����Ա'
end
from emp;
decode����
decode(col | expression, search1, result1,
						[,search2, result2,...,]
						[,default])
decode ������case���ʽ����������if-then-else �߼��ж�
select empno, ename, job,decode(job, 'clerk', '����Ա'��'salesman', '����'��'�ܲ�') from emp;
select empno, ename, sal,
case when sal<2000 then '��'
when sal < 5000 then '��'
else '��'
end
from emp;
���к�������Ƕ��
Ƕ�׺�����ִ��˳�������ڵ����
�������1
1>���չ�Ա��Ϣ������ʾ��Ƹ������3���º����һ����һ�����ڣ������ڸ�ʽΪ2017-01-06
����
��Ƹ������3���º�
add_months(hiredate,3)
��һ����һ
next_day(add_months(hiredate, 3), '����һ')
�����ڸ�ʽ����2017-01-06
to_char(next_day(add_months(hiredate,3),'����һ')��'YYYY-MM-DD')
�������2
2>���չ�Ա��Ϣ����ʾ��Ա���±��������뵽2ΪС���Ľ����Ȼ���н�ʸ�ʽ��'��1,182.19'���������ӽ��и�ʽ��
����
��Ա���²��������뵽2����С���Ľ��
round(sal/30, 2)
��н�ʸ�ʽ��'��1,182.19'���������ӽ��и�ʽ��
to_char(round(sal/30, 2),'L9,999.99')
6-1 Oracle���麯��(���к���):������һ�����ݣ�����һ�����ݷ���һ��ֵ
�ڹ�ϵ���ݿ��У�ʹ�����ݷ������ȡ�ñ����ݵĻ�����Ϣ�����ݷ�����ͨ�����麯��,group by �Լ�having���Ӿ乲ͬʵ�ֵ�

avg:
select avg(sal) from emp;
sum:
min:
max:
count��
select count(*) from emp; --ȫ��
select count(empno) from emp; --���Կ�ֵ
select count(distinct empno) from emp; --ȥ���ظ���¼
wm_concat���ú��������ò�ѯ�����ת�У����԰���ֵ��','�ŷָ�����������ʾ��һ�С�
select wm_conncat(ename) from emp;
���麯�����ֵ
ʹ�÷��麯���и���Ҫ��������ǿ�ֵ����
eg:
��Ա����ƽ������
��Ա����ƽ������
>���麯�����Զ����Կ�ֵ
>nvl����ʹ���麯���޷����Կ�ֵ
select count(nvl(comm,0))from emp;

6-2 Oracle�ķ��麯��-group by
group by �Ӿ������:���Խ����е����ݷֳ�������
group by �Ӿ���﷨:
select [column,] group function(column),...
from table
[where condition]
[group by group_by_expression]
[having group_condition]
[order by column];
eg:
select depno, avg(sal) from emp group by depno;
select�б��е��б��������group by �麯���б���
eg:select depno, avg(sal) from emp  ERR!!!
select depno, job, avg(sal) from emp group by depno, job;
select avg(sal) from emp group by depno;--������group by �е��У����ذ�����select �б��С�
select deptno, wm_concat(ename) from emp group by depno;
6-3 Oracle�ķ��麯��--having
����:���ڶԷ����Ľ�����й���
eg:��ƽ�����ʴ���2500�Ĳ��ţ�Ҫ����ʾ�����źţ�ƽ������
select deptno, avg(sal) from emp group by deptno having avg(sal) > 2500;
ע�⣺������where�Ӿ���ʹ�÷��麯����������having�Ӿ���ʹ���麯����
select deptno, avg(sal) from emp where avg(sal) > 2500 group by deptno;  ERR!!!
���������û���麯��������ʹ��where ���Ϳ���
eg:
select deptno, avg(sal) from emp where deptno = 10 group by deptno;
where ʹ�÷����¼��󽵵ͣ��Ӷ����Ч��
��SQL�Ż��Ƕȿ�������ʹ��where �Ӿ䡣�ȹ��˺���顣
���麯����Ƕ��--����ʹ��group by �Ӿ�
select mac(avg(sal)) from emp group by deptno;
7-1 �ѿ�����
�ѿ������Ǽ��ϵ�һ�֣�����A��B���Ǽ��ϣ�A��B�ĵѿ�������A*B����ʾ��A*B���γɵļ��Ͻеѿ�����
�������--�������
Ϊ�˱���ѿ�������������where�Ӿ��м�����Ч����������
��������������n-1����n�����ĸ���
�ڱ�������ͬ��ʱ��������֮ǰ���ϱ���ǰ׺��
Oracle���������Ӳ�ѯ
>��ֵ����
��ֵ������ָʹ�õ�ֵ�ȽϷ�(=)ָ�����������Ĳ�ѯ
select empno, ename, job, dname from emp, dept where emp.deptno = dept.no;
ʹ�ñ���ǰ׺�ڶ������������ͬ���У����ִ��Ч��
ʹ�ñ�ı��������Լ����Ӳ�ѯ����߲�ѯ����
select e.empno, e.ename, e.job, d.dnamefrom emp e, dept d where e.deptno = d.deptno;
�����Ӳ�ѯ�У����ж����������ʱ��ʹ��andָ������������
select e.empno, e.ename, e.job, d.dnamefrom emp e, dept d where e.deptno = d.deptno and d.depno = 10;
>�ǵ�ֵ����
����ֵ������ָʹ�ó���ֵ�ȽϷ�֮��������Ƚϲ���ִ�����Ӳ�ѯ
select e.empno, e.sal, s.grade from emp e, salgrade s where e.sal between losal and hisal;
>������
�����ӵ�ʵ����:��ͬһ�ű����Ƕ��ű�
select e.ename, m.ename from emp e, emp m where e.mgr = m.empno;
>������
�������Ǳ�׼���ӵ���չ���������᷵���������������м�¼�����һ��᷵�ز����������Ĳ��ּ�¼
select d.deptno, d.dname, count(e.empno) from dept d, emp e where d.deptno =  e.deptno group by d.depno, d.dname;
���ű��Ϊ40�Ĳ��ţ�Ա����Ϊ0��û����ʾ����
�������﷨
��������ʹ��(+)��������ɵġ�
��(��)����:
select table.column, table2.column
from table1, table2
where table1.column(+) = table2.column;
���ص��ǵȺ��ұ߱��ȫ����¼(���������������ļ�¼)�����صȺ�������������ļ�¼
��(��)����
select table1.column, table2.column
from table1, table2
where table1.column = table2.column(+)
���ص��ǵȺ���߱��ȫ����¼
SQL��1999��׼�﷨���Ӳ�ѯ
Ϊ�˼򻯲�ѯ��ʹ�ò�ѯ����ֱ�ۣ������ױ�д��SQL��1999��׼Ϊ���Ӳ�ѯ�ṩ�����﷨��
select table1.cloumn_name, table2.column_name from table1
[cross join table2] | [natural join table2] |
[join table2 usign(column_name)] |
[join table2 on (table.column_name = table2.column_name)] |
[left | right | full outer join table2 on (table1.column_name = table2.column_name)];
��������cross join(�˽�)
���صѿ������ò���
select d.dname, e.ename, d.deptno, e.deptno from dept d, emp e;
corss join ����Ҳ�����������ű�õѿ�����(�漯)
select d.dname, e.ename, d.deptno, e.deptno from dept d cross join emp e;
��Ȼ����natural join
��Ȼ������һ������õȼ����ӣ��������о�����ͬ���Ƶ��н��м�¼ƥ�䡣��Ȼ���Ӳ���ָ���κ�ͬ����������.
select table1.column_name, table2.column_name from table1 natural jion table2;
������ [inner] jion
��������������ƥ������ݣ�ֻ�����������������ݣ�����ֵ���ӣ��ǵ�ֵ���ӣ���Ȼ���Ӷ�����������������
��using�Ӿ佨���������
select e.name, e.sal, d.dname, from dept d [inner]jion emp e using(deptno);
��on�Ӿ佨���������
select e.ename, e.sal, d.dname from dept d jion emp e on deptno = d.deptno;
���⣩����left [outer] jion
�����������ڷ��������������������ݣ��Լ�����������������������������(��������ȫ����¼���ұ����������ļ�¼)
��SQL:1999��׼�У���������ͨ��left[outer]jion ѡ����ʵ�ֵ�
select e.ename, e.sal, d.dname, from dept d left jion emp.e on e.deptno = d.deptno;
�ң��⣩����right [outer] jion
��ȫ���⣩����full [outer] join
��ȫ�������ڷ��������������������ݣ��Լ�������������������߱���ұ߱���������ݣ����������ұ��ȫ����¼��
select e.ename, e.sal, d.dname from dept d full jion emp e on e.deptno = d.deptno;
Orcle��set�����
���ϲ�����ר�źϲ�����select ���Ľ��������4�֣�
union/union all ���� 
{1,2,3} union {3,4} = {1,2,3,4} 
{1,2,3} union all {3,4} = {1,2,3,3,4}
union ����������ȡ������������Ĳ�������ʹ�øò�����ʱ�����Զ�ȥ��������е��ظ��У����һ��Ե�һ�еĽ�������������С�
create table emp01 as select * from emp where deptno in(10, 20);
create table emp02 as select * from emp where deptno in (20,30);
select deptno, empno, ename from emp01 
union
select deptno, empno, ename from emo02;  
union all ����������ȡ������������Ĳ���������union��������ͬ���ò���������ȡ���ظ��У����Ҳ���Խ�������ݽ�������
intersect ����
intersect����������ȡ������������Ľ�������ʹ�øò�����ʱ��ֻ����ʾͬʱ����������������е����ݣ����һ��Ե�һ�еĽ�������������С�
minus �
minus����������ȡ������������Ĳ����ʹ�øò�����ʱ��ֻ����ʾ�ڵ�һ��������д��ڣ��ڶ���������в����ڵ����ݡ����һ��Ե�һ�еĽ���������������С�
���ƽ������
��ʹ�ü��ϲ�����union��intersect��minusʱ��Ĭ������»��Զ����ڵ�һ�н����������򣻶���ʹ�ü��ϲ�����union all ʱ�������������Ϊ�˿��ƽ��������˳�򣬿���ʹ��order by �Ӿ䡣
select depno, emni, ename from emp01 
union all 
select depno, empno, ename from emp02 
order by 1;
ʹ��set ��������ע������
��select�б��е������ͱ��ʽ������������������Ҫ���Ӧ
8-1 Oracle���Ӳ�ѯ
�Ӳ�ѯ��ָǶ��������sql����е�select ��䣬Ҳ��Ƕ�ײ�ѯ��
select * from emp where job = (select job from emp where ename = 'SMITH')��
--ddl����е��Ӳ�ѯ
create table empnew as select * from emp;
�Ӳ�ѯ���﷨
select select_list
from table
where expr operator
			��select select_list
			from table��;
�������Ӳ�ѯ��λ�ã�where, select, having, from 
--
select deptno, dname, loc,(select count(empno) from emp where emp.deptno = dept.deptno) cnt from dept;
select deptno, avg(sal) from emp group by deptno having avg(sal) > (select max(sal) from emp where deptno = '30')
select ename, job, sal from emp,(select deptno, avg(sal) from emp group by deptno) avgsal where emp.deptno = dept.deptno and sal > avgsal;  
8-2 Oracle ������ѯ���Ӳ�ѯ
select * from where job = (select job from emp where empno  = 7521) and sal > (select sal from emp where empno = 7934);
һ����ִ���Ӳ�ѯ�� ��ִ������ѯ��������Ӳ�ѯ���⡣
select epno, ename, sal from emp where sal < (select avg(sal) from emp);
����Ӳ�ѯ
���Ӳ�ѯ��Ҫ��������ѯ���б�ʱ��Oracle��ִ������Ӳ�ѯ��
����Ӳ�ѯ����ִ������ѯ����ִ���Ӳ�ѯ��
select ename, sal, deptno from emp e where sal > (select avg(sal) from emp where deptno = e.deptno);
����ѯ���Ӳ�ѯ���Բ���ͬһ�ű�
select * from emp where deptno = (select deptno from dept where dname = 'accounting');
select e.* from emp e, dept d where e.deptno = d.deptno and d.dname = 'accounting';
8-3 Oracle �ĵ����Ӳ�ѯ
�����Ӳ�ѯ
ֻ����һ�����ݵ��Ӳ�ѯ��䣬ʹ�õ��бȽϲ�����
=, >=, <>, <=, >, <,
select ename, sal, deptno from emp where deptno(select deptno from emp where ename='james') and ename <> 'james'
select ename, job, sal from emp where sal >= (select avg(sal) from emp);
select * from emp where deptno <> (select deptno from dept where dname = 'saves');
�Ƿ�ʹ�õ����Ӳ�ѯ
select ename, job, sal from emp where sal = (select max(sal) from emp group by deptno)
�����Ӳ�ѯ
�����Ӳ�ѯ��ָ���ض������ݵ��Ӳ�ѯ���
ʹ�ö��бȽϲ�����
in, �����б��е��κ�һ��
select * from emp where deptno in (select deptno from dept where loc = 'new york' or lock = 'chicago');
all,���Ӳ�ѯ���ص�����ֵ���бȽ� //���ܵ���ʹ��
select ename, sal, depno from emp where sal > all(select sal from emp where deptno = 30)
select ename, sal, deptno from emp where sal > (select max(sal) from emp where deptno = 30)
any�����Ӳ�ѯ���ص�����ֵ���бȽ�//���ܵ���ʹ��
select ename , sal, deptno from emp where sal > any(select sal from emp where depno = 10);
8-5 Oracle�Ӳ�ѯ��Ҫע�������
��������group by�Ӿ���ʹ���Ӳ�ѯ
select avg(sal) from emp group by (select deptno from emp)
��top_n���������У�����Ӳ�ѯ����
eg:��ʾԱ����Ϣ���й�����ߵ�ǰ����Ա��
select rownum, empno, ename, sal from (select * from emp order by sal desc);
select empno, ename, sal from emp where rownum <= 5 order by sal desc;
select rownum, empno, ename, sal from (select * from emp order by sal desc) where rownum <= 5;
�����Ӳ�ѯ�Ͷ����Ӳ�ѯ�еĿ�ֵ����
�����Ӳ�ѯ�Ŀ�ֵ����
select ename, job from emp where job = (select job from emp where ename = 'ruby');
����Ӳ�ѯ������һ����ֵ��������ѯ�������ѯ���κν��
�����Ӳ�ѯ�Ŀ�ֵ����
select * from emp where empno not in (select mgr from emp);
����Ӳ�ѯ������һ����ֵ��������ѯ�������ѯ���κν��
9-Oracle ���ݶ���--��ͼ
���������ݿ����
��		���������ݴ洢���ϣ����к������
��ͼ	�ӱ��г�����߼���ص����ݼ���
����	�ṩ�й��ɵ���ֵ
����	��߲�ѯ��Ч��
ͬ���	��������ı���
��ͼ��һ������ı�
��ͼ���������б�Ļ����ϣ���ͼ���Խ�������Щ��λ����
����ͼ�ṩ�������ݵ����Ϊselect���
1.��ȫԭ���������ݷ���
2.��ͼ����ʹ���ӵĲ�ѯ��������ʹ��
��ͼ�ķ���
����ͼ
���ڵ�������	ʾ��һ���������ڲ�ѯԱ���ţ����������ʵ���ͼ
system: grant create view to scott;
create view emp_view
as
select empno, ename, sal from emp;

create view emp_view2(Ա���ţ�����������)
as 
select empno, ename, sal from emp;
������ͼ
������ͼ
ʾ�������������ڻ�ò��ź�Ϊ10�Ĳ��źţ����������Լ�Ա����Ϣ
create view dept_emp_view
as 
select d.deptno,d.dname, e.empno, e.job
from dept d, emp e
where d.deptno = e.deptno and d.deptno = 10;
select * from dept_emp_view
ֻ����ͼ
ʾ�����������鿴10�Ų���Ա����Ϣ����ͼ
create view emp_view
as
select * from emp where deptno = 10
with read only; 
������ͼ���﷨��ʽ
create [or replace] view view[(alias[,alias]...)]
as subquery
[with check option [constraint constraint]]
[with read only]
9-2 Oracle��ͼ���޸���ɾ��
��ͼ�ϵ�DML����
��ѯ��ͼ
select * from empnew_view;
�������-insert
insert into empnew_view (empno, ename, sal) values(888, 'layna', 6666);
�޸����� update
update empnew_view set sal = sal + 100 where empno = 888
ɾ������ delete
delete from empnew_view where empno = 8888;
ע�⣺
�����ͼ�ĸ��²�����insert, update, delete��ʵ�ʸı���ǻ����е�����
�ڴ�����ͼʱ����checkԼ��(with check option)
create view empnew_view
as 
select * from empnew where deptno = 20
with check option constriant chk_view
��update/insert����Ϣ��������deptno = 20 ��Υ��checkԼ����
�޸���ͼ
ʹ��create or replace view �Ӿ��޸���ͼ
create or replace view emp_view 
as 
select * from emp where job = 'salesman';
ɾ����ͼ
��ʱͼ������Ҫʱ���û�����ִ��drop view ���ɾ����ͼ
drop view view ;
9-3������ͼ
������ͼ��ָ�������������ʽ���߷������ݵ���ͼ������Ҫ����ִ�в�ѯ����
ע�⣺�����帴����ͼʱ������ҪΪ�������߱��ʽ�����б�����
ʵ����
�������ڻ��ÿ����λƽ�����ʣ������ܺͣ���߹��ʺ���͹��ʵ���ͼ��
create view job_view(job, avgsal, sumsal, maxsal,minsal)
as
select job, avg(sal), sum(sal), max(sal), min(sal)
from emp
group by job;
������ͼ��ִ��DML������ԭ��
delete������ԭ��
��ͼ�а�������Ԫ��֮һ����ִ��delete������
group by �Ӿ�
���麯��
distinct �ؼ���
rownumα��
update����ԭ��
��ͼ�а�������Ԫ��֮һ����ִ��update������
group by �Ӿ�
���麯��
distinct �ؼ���
rownumα��
ʹ�ñ��ʽ�������
insert����ԭ��
��ͼ�а�������Ԫ��֮һ����ִ��insert������
group by �Ӿ�
���麯��
distinct �ؼ���
rownumα��
ʹ�ñ��ʽ�������
��ͼ��û�а��������not null ��




















