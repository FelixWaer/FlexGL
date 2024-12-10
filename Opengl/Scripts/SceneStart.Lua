id = create_Entity()

add_Component(id, "PositionComponent")
add_Component(id, "MovementComponent")
add_Component(id, "TransformComponent")
add_Component(id, "MeshComponent")
add_Component(id, "PhysicsComponent")
add_Component(id, "SphereCollComponent")
add_Component(id, "ScriptComponent")

set_Mesh(id, "Cube")
set_Script(id, "Scripts/TriggerScript.Lua")
set_CollisionRadius(id, 0.5)

pos = get_Position(id)
pos.y = 10
set_Position(id, pos)
print(id)