# Ruby mystery

rb_hash_aset seems to perform poorly along with PQexec

* PQexec seems to make rb_hash_aset slow
* There is no iteration over results of any sort

## Setup

* ruby 1.9.3p125
* create database `createdb slow_hash_aset`
* create some sample data

```
psql slow_hash_aset -c 'drop table if exists users'
psql slow_hash_aset -c "create table users as select id, 'name ' || id as name, now() as created_at from (select generate_series(1, 1000) as id) u"
```

## Run Bechmarks

```
 $ ruby extconf.rb
 $ make
 $ ruby check.rb 
                                     user     system      total        real
PQexec without rb_hash_aset      0.050000   0.010000   0.060000 (  0.197877)
rb_hash_aset without PQexec      0.070000   0.000000   0.070000 (  0.068446)
PQexec with rb_hash_aset         0.260000   0.010000   0.270000 (  0.618619)
```
