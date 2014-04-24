
function createRobot(name)
   local obj = {name = name}
   function obj:SetName(name)
      self.name = name
   end
   obj.GetName = function(self)
      return self.name
   end
   return obj
end

-- inherit

function createFootballRobot(name, position)
   local obj = createRobot(name)
   obj.position = position
   obj.SetPosition = function(self, p)
      self.position = p
   end
   function obj.GetPosition(self)
      return self.position
   end
   
   return obj
end

r = createFootballRobot("John", "right back")
print(r:GetName(), r.GetPosition(r))
r.SetName(r, "Helen")
r:SetPosition("front")
print(r:GetName(), r.GetPosition(r))
