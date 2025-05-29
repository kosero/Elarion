use macroquad::prelude::*;

mod player;
use player::Player;

#[macroquad::main("test")]
async fn main() {
    let mut player = Player::new("emirhan".to_string());
    let texture = Player::set_texture("assets/player.png").await;

    let width = screen_width();
    let height = screen_height();

    player.position = vec2(width / 2.0, height / 2.0);

    loop {
        let delta = get_frame_time();

        clear_background(LIGHTGRAY);
        set_camera(&player.camera);

        player.update(&texture, delta);
        draw_rectangle(width / 2. - 20., height / 2. - 20., 20., 20., RED);
        next_frame().await
    }
}
