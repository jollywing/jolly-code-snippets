
#include <stdio.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#define lua_open() luaL_newstate()
lua_State * L;

// call function in lua script
int luaadd(int x, int y)
{
  int sum;
  lua_getglobal(L, "add");
  lua_pushnumber(L, x);
  lua_pushnumber(L, y);

  // call function 'add' in script, 2 arguments, return 1 result
  lua_call(L, 2, 1);
  sum = (int)lua_tointeger(L, -1);
  lua_pop(L, 1);
  return sum;
}

// provide lua function
static int average(lua_State *L)
{
  // get number of arguments
  int n = lua_gettop(L);
  double sum = 0;
  int i;
  for (i = 1; i <= n; i++) {
    sum += lua_tonumber(L, i);
  }
  lua_pushnumber(L, sum/n);
  lua_pushnumber(L, sum);
  return 2;
}

int main(int argc, char *argv[])
{
  L = lua_open();
  luaL_openlibs(L);

  // register our function
  lua_register(L, "average", average);

  luaL_dofile(L, "test.lua");

  int i, j, sum;
  printf("Now call 'add' function defined in lua, input tow integers:\n");
  scanf("%d %d", &i, &j);
  sum = luaadd(i, j);
  printf("The sum is %d.\n", sum);
  lua_close(L);

  printf("Press any key to exit...\n");
  getchar();

  return 0;
}
