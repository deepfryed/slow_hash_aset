#!/usr/bin/env ruby

require 'mkmf'

$CFLAGS   = '-std=c99 -Os'

inc_paths = %w(
  /usr/include/postgresql
  /usr/local/include/postgresql
  /opt/local/include
  /opt/local/include/postgresql90
  /opt/local/include/postgresql85
  /opt/local/include/postgresql84
  /sw/include
)

lib_paths = %w(
  /usr/lib
  /usr/local/lib
  /opt/lib
  /opt/local/lib
  /sw/lib
)

find_header('libpq-fe.h',  *inc_paths) or raise 'unable to locate postgresql headers'
find_library('pq', 'main', *lib_paths) or raise 'unable to locate postgresql lib'

create_makefile('slow_hash_aset')
