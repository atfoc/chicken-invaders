# Class list

## Class list for rg::engine
+ window
+ event
 + built_in
 + user_event target_event
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
+ [ ] move assignment [ ] attach_scene(scene_id)
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
+ [ ] static logger()

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
+ [ ] virtual copy
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
+ [x] constructor(position, color)
+ [x] position
+ [x] color
+ [x] turn_on(id)
+ [x] apply(id)
+ [x] turn_off(id)

### rg::engine::color
+ [x] constructor(string hex html color)
+ [x] constructor(r, g, b)
+ [x] html_color
+ [x] red
+ [x] green
+ [x] blue

### rg::engine::camera
+ [x] constructor()
+ [x] copy constructor
+ [x] virtual apply
+ [x] virtual deconstructor


### rg::engine::orthogonal_camera
**extends rg::engine::camera**
+ [x] constructor(left, right, up, down, near, far)
+ [x] move(x, y)
+ [x] set_near_clip(near)
+ [x] set_far_clip(far)
+ [x] get_near_clip
+ [x] get_far_clip

### rg::engine::perspective_camera
**extends rg::engine::camera**
+ [x] constructor(eye, point,fovy, aspect, znear, zfar)
+ [x] copy_constructor
+ [x] eye
+ [x] point
+ [x] set_eye
+ [x] set_point
+ [x] fovy
+ [x] set_fovy
+ [x] aspect
+ [x] set_aspect
+ [x] near
+ [x] far
+ [x] set_near
+ [x] set_far
