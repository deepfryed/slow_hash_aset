# rb_hash_aset mystery

rb_hash_aset seems to perform poorly along with PQexec

## Setup

* ruby 1.9.3p125

```
 $ ruby extconf.rb
 $ make
 $ ruby check.rb 
                                     user     system      total        real
PQexec without rb_hash_aset      0.050000   0.010000   0.060000 (  0.197877)
rb_hash_aset without PQexec      0.070000   0.000000   0.070000 (  0.068446)
PQexec with rb_hash_aset         0.260000   0.010000   0.270000 (  0.618619)
```
