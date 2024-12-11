isHit = is_Colliding(EntityID)

if isHit == true then
    print("BIP BIP HIT!")
    remove_Component(EntityID, "SphereCollComponent")
    render_Mesh(EntityID, false)

    for i = 0, 2 do
    id = create_Entity()

    add_Component(id, "PositionComponent")
    add_Component(id, "MovementComponent")
    add_Component(id, "TransformComponent")
    add_Component(id, "MeshComponent")
    add_Component(id, "PhysicsComponent")
    add_Component(id, "SphereCollComponent")

    set_Mesh(id, "Cube")
    set_CollisionRadius(id, 0.5)

    pos = {}
    pos.x = i * 2
    pos.y = 10
    pos.z = 0
    set_Position(id, pos)
    end
end
