
function foo()
   return 'a','b'
end

print(foo())
print(foo() .. 'ge')
print(foo(), 0)

t = {foo()}
print(t[1], t[2])