
-- 函数闭包
function createCountDownTimer(second)
   local ms = second * 1000
   -- ms is upvalue to countDown
   -- countDown and ms make up 函数闭包
   -- 函数闭包 can hold values of upvalue
   local function countDown()
      ms = ms - 1
      return ms
   end
   return countDown
end

timer1 = createCountDownTimer(1)
for i = 1, 5 do
   print(timer1())
end

print('----------------------------')

timer2 = createCountDownTimer(2)
for i = 1, 5 do
   print(timer2())
end
