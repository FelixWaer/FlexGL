
rot = get_Rotation(EntityID)
rot.y = rot.y + 0.01
set_Rotation(EntityID, rot)

acc = get_Acceleration(EntityID)
acc.x = acc.x + 10
--set_Acceleration(EntityID, acc)
set_Mesh(EntityID, "Cube")