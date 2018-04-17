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
+ scene
+ game_object
+ light
+ camera

## Class method list

### rg::engine::window
+ constructor(name, posx, posy, width, height, hidden = false)
+ move constructor
+ move assignment
+ attach_scene(scene)
+ attahc_camera(camera_id, view_port)
+ detach_scene
+ handle_event(event)
+ id
+ has_scene

### rg::engine::event
+ constructor
+ move constructor
+ copy constructor
+ virtual type
+ virtual get_sdl_event
+ virtual assign
+ operator = &
+ virtual move
+ operator =&&
+ virtual deconstructor

### rg::engine::built_in_event
**extends rg::engine::event**
+ constructor(SDL_Event)
+ copy constructor
+ move constructor
+ operator =&
+ operator =&&

### rg::engine::user_event
**extends rg::engine::event**
+ constructor(scene_id)
+ copy constructor
+ move constructor
+ operator =&
+ operator =&&
+ virtual code
+ scene_id
+ static register_event
Advice is provide static function for returning event
code received from register_event

### rg::engine::target_event
**extends rg::engine::user_event**
+ constructor(scene_id, obj_id)
+ copy constructor
+ move constructor
+ operator =&
+ operator =&&
+ obj_id

### rg::engine::thread
+ constructor(function ,args)
+ move = delete
+ copy = delete
+ operator =& =delete
+ operator =&& = delete
+ join

### rg::engine::timer
+ constructor(timems, scene_id, obj_id, timer_id)
+ copy = delete
+ move constructor
+ move assignment
+ start
+ stop
+ pause

### rg::engine::log
+ static init(to_file : boolean, base_name)
+ static danger//red
+ static info//green
+ static debug//blue
+ static warning//yellow

### rg::engine::application
+ static create_window(name, px, py, w, h, hidden)
+ static create_thread(function, args)
+ static post_event(event)
+ static init(argc, argv)
+ static add_scene(scene)
+ static attach_scene_to_window(widnow_id, scene_id)
+ static attach_camera_to_window(window_id, camera_id, view_port)
+ static detach_camera_from_window(window_id, camera_id)
+ static detach_scene_from_window(window_id)
+ static main_loop

### rg::engine::scene
+ add_object(game_object, pos)
+ get_object(id)
+ collision(object)
+ pause
+ resume
+ broadcast(event)
+ notify(object, event)
+ remove_object(id)
+ get_objects
+ render
+ handle_event

### rg::engine::game_object
+ virtual on_frame
+ virtual handle_event
+ virtual on_collision
+ pos
+ set_pos(pos)

### rg::engine::id
+ static random_id
+ static name_id
+ static null_id
+ static is_null_id

**TODO cameras and lights**
