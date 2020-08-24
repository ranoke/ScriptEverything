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

