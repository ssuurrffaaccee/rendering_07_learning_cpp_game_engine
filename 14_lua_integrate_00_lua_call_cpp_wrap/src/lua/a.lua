-- None
local player = Player()
-- -1 PlayerPointer
print(player)

print("player.hp_:" .. player.hp_)
print("player.AddHp(4):" .. player:AddHp(4))
print("player.hp_:" .. player.hp_)