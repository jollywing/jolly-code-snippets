
-- Here b is a hash table
-- why is "hello" in brackets?
b = { x = 1, ["hello"] = "world"}

for k, v in pairs(b) do
   print(k, "==>", v)
end
print('-------------------------')

function foo()
end

function bar()
end

-- here a is a empty hash table
a = {}
-- the pair in lua table can be heterogenous
-- a.astring equals a["astring"]
-- a.astring = "Hello"
a['astring'] = "Hello"
a[1] = 100

-- foo and bar must be defined ahead.
-- a.foo is not equal to a[foo]
-- a.foo = bar
a[foo] = bar
a.atable = b

for k, v in pairs(a) do
   print(k, "==>", v)
end

print('----------------------------')
-- delete foo
a[foo] = nil
print(a[foo])
