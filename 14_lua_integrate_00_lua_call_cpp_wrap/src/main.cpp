
extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}
#include <stdio.h>
#include <string.h>

#include <memory>
#include <string>

using namespace std;

class Player {
 public:
  int AddHp(int add) {
    hp_ += add;
    return hp_;
  }

  int hp_ = 0;
};

static int CreatePlayer(lua_State* L) {
  // new Stack Frame
  Player** pData = (Player**)lua_newuserdata(L, sizeof(Player*));
  *pData = new Player();
  // -1 PlayerPointer
  luaL_getmetatable(L, "Player");
  // -1 PlayerMetaTable
  // -2 PlayerPointer
  lua_setmetatable(L, -2);  // 将-1处的MetaTable附加到-2处的值中
  // -1 PlayerPointer
  return 1;  // return top
}

static int DestroyPlayer(lua_State* L) {
  // new Stack Frame
  // 栈底元素
  delete *(Player**)lua_topointer(L, 1);
  return 0;
}

static int CallAddHp(lua_State* L) {
  // new Stack Frame
  Player* pPlayer = *(Player**)lua_topointer(L, 1);
  lua_pushnumber(L, pPlayer->AddHp(lua_tonumber(L, 2)));
  return 1;  // return top
}

static int lua_index(lua_State* L) {
  // new Stack Frame
  Player* pPlayer = *(Player**)lua_topointer(L, 1);

  if (strcmp(lua_tostring(L, 2), "hp_") == 0) {
    // -1 "hp_"
    // -2 PlayerPointer
    lua_pushnumber(L, pPlayer->hp_);
    // -1  hp_
    // -2 "hp_"
    // -3 PlayerPointer
  } else if (strcmp(lua_tostring(L, 2), "AddHp") == 0) {
    // -1 "AddHp"
    // -2 PlayerPointer
    lua_pushnumber(L, pPlayer->hp_);
    // -1 hp_
    // -2 "AddHp"
    // -3 PlayerPointer
    lua_pushcfunction(L, CallAddHp);
    // -1 CallAddHp
    // -2 hp_
    // -3 "AddHp"
    // -4 PlayerPointer
  } else {
    return 0;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  lua_State* L = luaL_newstate();
  luaopen_base(L);
  // None
  lua_pushcfunction(L, CreatePlayer);
  // -1 CreatePlyaerFunc
  lua_setglobal(L, "Player");
  // None
  luaL_newmetatable(L, "Player");
  //-1 PlayerMetaTable
  lua_pushstring(L, "__gc");
  // -1 __gc
  // -2 PlayerMetaTable
  lua_pushcfunction(L, DestroyPlayer);
  // -1 DestroyPlayerFunc
  // -2 __gc
  // -3 PlayerMetaTable
  lua_settable(L, -3);
  // -1 PlayerMetaTable
  lua_pushstring(L, "__index");
  // -1 __index
  // -2 PlayerMetaTable
  lua_pushcfunction(L, lua_index);
  // -1 LueIndexFunc
  // -2 __index
  // -3 PlayerMetaTable
  lua_settable(L, -3);
  // -1 PlayerMetaTable
  lua_pop(L, 1);
  // None
  luaL_dofile(L, "./lua/a.lua");

  lua_close(L);

  return 0;
}
