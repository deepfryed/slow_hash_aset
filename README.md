# rb_hash_aset mystery

rb_hash_aset seems to perform poorly along with PQexec

## Setup

* ruby 1.9.3p125

```
 $ ruby extconf.rb
 $ make
 $ ruby check.rb 
                                     user     system      total        real
execute without rb_hash_aset     0.060000   0.000000   0.060000 (  0.192783)
rb_hash_aset without execute     0.070000   0.000000   0.070000 (  0.070356)
execute with rb_hash_aset        0.250000   0.020000   0.270000 (  0.632042)
```
