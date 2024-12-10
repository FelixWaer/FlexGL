--pos = get_Position(EntityID)
rot = get_Rotation(EntityID)
--pos.x = pos.x + 0.001
rot.y = rot.y + 0.01
--set_Position(EntityID, pos)
set_Rotation(EntityID, rot)
acc = get_Acceleration(EntityID)
acc.x = acc.x + 10
--set_Acceleration(EntityID, acc)
set_Mesh(EntityID, "Cube")