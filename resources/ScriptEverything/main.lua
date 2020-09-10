
function OnRender()
    Draw.DrawRect({640/2,480/2}, {100, 70}, {50,50,90}, 2.3)
    Draw.DrawCrosshair(20,20,160)
    mod = GetModule("ac_client.exe")
    res = Mem.ReadInt(mod + tonumber("0x109B74"))
    res = Mem.ReadInt(res + tonumber("0x374"))
    res = Mem.ReadInt(res + tonumber("0x14"))
    ammo = Mem.ReadInt(res + tonumber("0x0"))
    print(ammo)
end

function main()
    print("Main()")
    
end