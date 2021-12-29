/*
use nannou::prelude::*;
use std::sync::{Mutex};
use lazy_static::lazy_static;
use std::thread::sleep;
use std::time::Duration;

lazy_static! {
    static ref GRID : Mutex<Vec<Vec<u8>>> = Mutex::new(Vec::new());
}

pub fn render(data: &mut Vec<Vec<u8>>) {
    for row in data.iter() {
        GRID.lock().unwrap().push(row.clone());
    }
    nannou::app(model).update(update).simple_window(view).run();
}
struct Model {}

fn model(_app: &App) -> Model {
    Model {}
}

fn update(_app: &App, _model: &mut Model, _update: Update) {
}

fn view(app: &App, _model: &Model, frame: Frame) {
    let mut data = GRID.lock().unwrap();
    crate::step(&mut data);

    let draw = app.draw();
    draw.background().color(BLACK);

    let win = app.window_rect();

    let block = win.pad(25.0).h() / (data[0].len() + 1) as f32;
    let origin = win.pad(25.0).top_left() + Point2::new(block, -block);
    for y in 0..data.len() {
        for x in 0..data[0].len(){
            let (x, y) = (x as f32, y as f32);
            let r= Rect::from_x_y_w_h(origin.x + x*block, origin.y - y * block, block, block);

            let hue ;
            let val ;
            let mut sat = data[y as usize][x as usize] as f32 ;
            if sat == 0.0 {
                sat = 1.0;
                hue = 0.0;
                val = 1.0;
            }
            else {
                sat = 1.0 - (sat / 9.0);
                hue = 117.0 / 255.0;
                val = sat / 9.0;
            }

            let c = hsva(
                hue,
                sat,
                val,
                1.0 - 0.5,
            );

            draw.rect()
                .xy(r.xy())
                .wh(r.wh())
                .stroke_weight(1.0)
                .color(c);
        }
    }
    draw.to_frame(app, &frame).unwrap();
    sleep(Duration::new(0, 10000000));
}
*/