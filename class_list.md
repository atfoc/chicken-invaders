# Class list

## Class list for rg::engine
+ window
+ event
 + built_in
 + user_event
 + target_event
+ thread
+ timer
+ application
+ log
+ scene game_object light
+ camera

## Class method list

### rg::engine::window
+ [ ] constructor(name, posx, posy, width, height, hidden = true)
+ [ ] copy_constructor = delete
+ [ ] move constructor
+ [ ] move assignment
+ [ ] attach_scene(scene_id)
+ [ ] attahc_camera(camera_id, view_port_function)
+ [ ] detach_camera(camera_id)
+ [ ] detach_scene
+ [ ] handle_event(event)
+ [ ] change_title
+ [ ] is_hidden
+ [ ] show(bool)
+ [ ] id
+ [ ] has_scene

### rg::engine::event
+ [x] constructor
+ [x] move constructor
+ [x] copy constructor
+ [x] virtual type
+ [x] virtual get_sdl_event
+ [x] virtual deconstructor

### rg::engine::built_in_event
**extends rg::engine::event**
+ [x] constructor(SDL_Event)
+ [x] copy constructor
+ [x] move constructor
+ [x] operator =&
+ [x] operator =&&

### rg::engine::user_event
**extends rg::engine::event**
+ [x] constructor(scene_id)
+ [x] copy constructor
+ [x] move constructor
+ [x] operator =&
+ [x] operator =&&
+ [x] virtual code
+ [x] scene_id
+ [x] static register_event
Advice is provide static function for returning event
code received from register_event

### rg::engine::target_event
**extends rg::engine::user_event**
+ [x] constructor(scene_id, obj_id)
+ [x] copy constructor
+ [x] move constructor
+ [x] operator =&
+ [x] operator =&&
+ [x] obj_id

### rg::engine::thread
+ [ ] constructor(function ,args)
+ [ ] move = delete
+ [ ] copy = delete
+ [ ] operator =& =delete
+ [ ] operator =&& = delete
+ [ ] join

### rg::engine::timer
+ [ ] constructor(timems, scene_id, obj_id, timer_id, repeat)
+ [ ] copy = delete
+ [ ] move constructor
+ [ ] move assignment
+ [ ] start
+ [ ] stop
+ [ ] pause

### rg::engine::log
+ [x] static init(to_file : boolean, base_name)
+ [x] static danger//red
+ [x] static info//green
+ [x] static debug//blue
+ [x] static warning//yellow

### rg::engine::application
+ [ ] static init(argc, argv)
+ [ ] static add_scene(scene)
+ [ ] static add_window(window)
+ [ ] static create_thread(function, args)
+ [ ] static post_event(event)
+ [ ] static main_loop

### rg::engine::scene
+ [ ] add_object(game_object, position)
+ [ ] get_object(id)
+ [ ] collision(object)
+ [ ] pause
+ [ ] resume
+ [ ] broadcast(event)
+ [ ] notify(object, event)
+ [ ] remove_object(id)
+ [ ] get_objects
+ [ ] render
+ [ ] handle_event

### rg::engine::game_object
+ [ ] virtual on_frame
+ [ ] virtual handle_event(event)
+ [ ] virtual on_collision
+ [ ] virtual render
+ [ ] virtual draw
+ [ ] apply_transformations
+ [ ] position
+ [ ] set_position(position)
+ [ ] rotation
+ [ ] set_rotation
+ [ ] scale
+ [ ] set_scale
+ [ ] move
+ [ ] rotate
+ [ ] stretch

### rg::engine::id
+ [x] static random_id
+ [x] static name_id
+ [x] static null_id
+ [x] static is_null_id
### rg::engine::light
+ [ ] constructor(position, color)
+ [ ] position
+ [ ] set_position
+ [ ] color
+ [ ] turn_on(light_id)
+ [ ] turn_off(light_id)

### rg::engine::color
+ [ ] constructor(string hex html color)
+ [ ] constructor(r, g, b)
+ [ ] html_color
+ [ ] red
+ [ ] green
+ [ ] blue

### rg::engine::camera
+ [ ] constructor()
+ [ ] virtual apply_transformation

### rg::engine::orthogonal_camera
**extends rg::engine::camera**
+ [ ] constructor(left, right, up, down, near, far)
+ [ ] move(vec2)
+ [ ] set_near_clip(near)
+ [ ] set_far_clip(far)
+ [ ] get_near_clip
+ [ ] near_clip
+ [ ] far_clip

### rg::engine::perspective_camera
**extends rg::engine::camera**
+ [ ] constructor(eye, point,fovy, aspect, znear, zfar)
+ [ ] eye
+ [ ] point
+ [ ] set_eye
+ [ ] set_point
+ [ ] fovy
+ [ ] set_fovy
+ [ ] aspect
+ [ ] set_aspect
+ [ ] near
+ [ ] far
+ [ ] set_near
+ [ ] set_far
