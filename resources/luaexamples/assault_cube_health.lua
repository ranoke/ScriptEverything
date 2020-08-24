mod = GetModule("ac_client.exe")
while true do
	res = ReadMemoryInt(mod, tonumber("0x109B74"))
	res = ReadMemoryInt(0, res + tonumber("0x374"))
	res = ReadMemoryInt(0, res + tonumber("0x14"))
	ammo = ReadMemoryInt(0, res + tonumber("0x0"))
	print(res)
	WriteMemoryInt(0, res + tonumber("0x0"), 2000)
end