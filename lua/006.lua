
function create(name, id)
   local data = {name = name, id = id}
   local obj = {}

   -- data is upvalue for obj.SetName
   function obj.SetName(name)
      data.name = name
   end

   function obj.GetName()
      return data.name
   end

   function obj.SetId(id)
      data.id = id
   end

   function obj.GetId(id)
      return data.id
   end

   -- Thus data is hidden to user
   return obj
end

o1 = create("Sam", 007)
print(o1.GetName(), o1.GetId())
o1.SetName("Herry")
o1.SetId(009)
print(o1.GetName(), o1.GetId())

