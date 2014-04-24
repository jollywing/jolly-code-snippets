
-- Object implementation
-- object factory pattern
function create(name, id)
   -- object is a table, no private member
   local obj = {name = name, id = id}
   -- there three methods to define function of a object
   -- 1 function obj:SetName(name)
   -- 2 function obj.SetName(self, name)
   -- 3 obj.SetName = function(self, name)
   function obj:SetName(name)
      self.name = name
   end
   function obj:GetName()
      return self.name
   end
   function obj:SetId(id)
      self.id = id
   end
   function obj:GetId()
      return self.id
   end
   return obj
end

o1 = create("Jimmy", 100)
print(o1:GetName(), o1:GetId())
-- o1:SetName("John"), equals
o1.SetName(o1, "John")
o1:SetId(200)
print(o1:GetName(), o1:GetId())
