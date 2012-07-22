# Ruby mystery

rb_hash_aset seems to perform poorly along with PQexec

* PQexec seems to make rb_hash_aset slow
* There is no iteration over results of any sort

## Setup

```
$ ruby -v
ruby 1.9.3p125 (2012-02-16 revision 34643) [x86_64-linux]

$ dpkg libpq5
Desired=Unknown/Install/Remove/Purge/Hold
| Status=Not/Inst/Conf-files/Unpacked/halF-conf/Half-inst/trig-aWait/Trig-pend
|/ Err?=(none)/Reinst-required (Status,Err: uppercase=bad)
||/ Name                        Version                     Description
+++-===========================-===========================-======================================================================
ii  libpq5                      9.1.3-2                     PostgreSQL C client library


# setup database & table
$ createdb slow_hash_aset
$ psql slow_hash_aset -c 'drop table if exists users'
$ psql slow_hash_aset -c "create table users as select id, 'name ' || id as name, now() as created_at from (select generate_series(1, 1000) as id) u"
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
