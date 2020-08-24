local f, error = loadfile("C:/ScriptEverything/luaext/keycodes.lua")
if not error then 
	f()
	print("Loaded keycodes")
end

client = GetModule("client.dll")

m_fFlags = tonumber("0xF9264")
dw_forceJump = tonumber("0x131424")

flags = 0
while true do
	flags = ReadMemoryInt(client, m_fFlags)
	if flags == 520 and IsKeyPressed(32) then
		WriteMemoryInt(client, dw_forceJump, 6)
	end
end

--mod = GetModule("ac_client.exe")
--while true do
--	res = ReadMemoryInt(mod, tonumber("0x109B74"))
--	res = ReadMemoryInt(0, res + tonumber("0x374"))
--	res = ReadMemoryInt(0, res + tonumber("0x14"))
--	ammo = ReadMemoryInt(0, res + tonumber("0x0"))
--	print(res)
--	WriteMemoryInt(0, res + tonumber("0x0"), 2000)
--end