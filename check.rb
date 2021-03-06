#!/usr/bin/env ruby

$:.unshift File.dirname(__FILE__)

require 'benchmark'
require 'slow_hash_aset'

iter = 100
Benchmark.bm(30) do |bm|
  hc = HC.new

  bm.report("PQexec without rb_hash_aset") do
    iter.times {hc.execute_no_aset {|r| r }}
  end

  bm.report("rb_hash_aset without PQexec") do
    iter.times {hc.no_execute {|r| r }}
  end

  bm.report("PQexec with rb_hash_aset") do
    iter.times {hc.execute {|r| r }}
  end
end
