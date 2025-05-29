use macroquad::color::WHITE;
use macroquad::experimental::animation::{AnimatedSprite, Animation};
use macroquad::input::KeyCode;
use macroquad::input::is_key_down;
use macroquad::math::Vec3;
use macroquad::text::draw_text;
use macroquad::text::measure_text;
use macroquad::texture::{DrawTextureParams, FilterMode, Texture2D, draw_texture_ex, load_texture};
use macroquad::window::{screen_height, screen_width};
use macroquad::{camera::Camera2D, math::Vec2};

pub enum PlayerState {
    IDLE,
    WALKING,
}

pub struct Player {
    pub name: String,
    pub position: Vec2,
    pub velocity: Vec2,
    pub speed: f32,
    pub camera: Camera2D,
    pub state: PlayerState,
    pub sprite: AnimatedSprite,
    pub frame: Vec3,
}

impl Player {
    pub fn new(name: String) -> Self {
        Self {
            name: name,
            position: Vec2::new(0., 0.),
            velocity: Vec2::new(0., 0.),
            speed: 300.,
            camera: Camera2D {
                ..Default::default()
            },
            state: PlayerState::IDLE,
            sprite: AnimatedSprite::new(
                16,
                16,
                &[Animation {
                    name: "player_n".to_string(),
                    row: 0,
                    frames: 4,
                    fps: 7,
                }],
                true,
            ),
            frame: Vec3::new(0., 1., 1.),
        }
    }

    pub async fn set_texture(texture_path: &str) -> Texture2D {
        let texture: Texture2D = load_texture(texture_path)
            .await
            .expect("[error]: Couldn't load file");
        texture.set_filter(FilterMode::Nearest);
        texture
    }

    pub fn set_animation(&mut self) {
        let sprite = AnimatedSprite::new(
            16,
            16,
            &[Animation {
                name: "player_n".to_string(),
                row: self.frame.x as u32,
                frames: self.frame.y as u32,
                fps: self.frame.z as u32,
            }],
            true,
        );
        self.sprite = sprite;
    }

    pub fn update(&mut self, texture: &Texture2D, delta: f32) {
        self.velocity = Vec2::ZERO;
        self.state = PlayerState::IDLE;

        let mut new_frame = self.frame;
        let mut is_moving = false;

        if is_key_down(KeyCode::W) || is_key_down(KeyCode::Up) {
            self.velocity.y -= 1.0;
            new_frame = Vec3::new(2., 4., 7.);
            is_moving = true;
        } else if is_key_down(KeyCode::S) || is_key_down(KeyCode::Down) {
            self.velocity.y += 1.0;
            new_frame = Vec3::new(0., 4., 7.);
            is_moving = true;
        } else if is_key_down(KeyCode::A) || is_key_down(KeyCode::Left) {
            self.velocity.x -= 1.0;
            new_frame = Vec3::new(1., 4., 7.);
            is_moving = true;
        } else if is_key_down(KeyCode::D) || is_key_down(KeyCode::Right) {
            self.velocity.x += 1.0;
            new_frame = Vec3::new(3., 4., 7.);
            is_moving = true;
        }

        if new_frame != self.frame {
            self.frame = new_frame;
            self.set_animation();
        }

        if is_moving {
            self.state = PlayerState::WALKING;
            self.velocity = self.velocity.normalize() * self.speed * delta;
            self.position += self.velocity;
            self.sprite.update();
        } else {
            self.state = PlayerState::IDLE;
            self.sprite.set_frame(0);
        }

        let player_frame = self.sprite.frame();

        let draw_size = Vec2::new(128.0, 128.0);
        let pos = Vec2::new(
            self.position.x - draw_size.x / 2.0,
            self.position.y - draw_size.y / 2.0,
        );

        draw_texture_ex(
            texture,
            pos.x,
            pos.y,
            WHITE,
            DrawTextureParams {
                dest_size: Some(draw_size),
                source: Some(player_frame.source_rect),
                ..Default::default()
            },
        );

        let text_dimensions = measure_text(&self.name, None, 32, 1.0);

        draw_text(
            &self.name,
            self.position.x - text_dimensions.width / 2.0,
            self.position.y - 80.,
            32.,
            WHITE,
        );
        self.camera.zoom = Vec2::new(2.0 / screen_width(), 2.0 / screen_height());
        self.camera.target = self.position;
    }
}
