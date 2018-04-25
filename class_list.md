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
+ [x] constructor(name, posx, posy, width, height)
+ [x] copy_constructor = delete
+ [x] move constructor
+ [x] move assignment 
+ [x] attach_scene(scene_id)
+ [x] attahc_camera(camera_id, view_port_function)
+ [x] detach_camera(camera_id)
+ [x] detach_scene
+ [x] handle_event(event)
+ [x] change_title
+ [x] is_hidden
+ [x] show(bool)
+ [x] id
+ [x] has_scene

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
+ [x] static init(argc, argv)
+ [ ] static add_scene(scene)
+ [x] static add_window(window)
+ [ ] static create_thread(function, args)
+ [x] static post_event(event)
+ [x] static main_loop
+ [x] static logger()

### rg::engine::scene
+ [x] add_object(game_object, position)
+ [x] get_object(id)
+ [x] collision(object)
+ [ ] pause events
+ [ ] resume events
+ [x] broadcast(event)
+ [x] notify(object_id, event)
+ [x] remove_object(id)
+ [ ] get_objects maybe implement this
+ [x] render
+ [x] handle_event
+ [x] add_camera(camera)
+ [x] remove_camera(camera_id)
+ [x] attach(window)
+ [x] detach(window)

### rg::engine::game_object
+ [x] virtual on_frame
+ [x] virtual handle_event(event)
+ [x] virtual on_collision
+ [x] virtual render
+ [x] virtual copy
+ [x] apply_transformations
+ [x] position
+ [x] set_position(position)
+ [x] rotation
+ [x] set_rotation
+ [x] scale
+ [x] set_scale
+ [x] move
+ [x] rotate
+ [x] stretch
+ [x] show()
+ [x] visable

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
+ [ ] virtual copy


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
