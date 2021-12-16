use nannou::prelude::*;
use std::cell::RefCell;
use std::sync::Arc;

static mut Data : Option<&'static mut Vec<Vec<u8>>> = None;

pub fn render(data: &mut Vec<Vec<u8>>) {
    Data = Some(data);
    nannou::sketch(view).size(800, 00).run();
}

fn view(app: &App, frame: Frame) {

    let draw = app.draw();
    draw.background().color(BLACK);

    let min_hue_value = 1.0;
    let max_hue_value = 0.98;
    let _win = app.window_rect();

    let hue = map_range(
        0.5,
        0.0,
        1.0,
        min_hue_value,
        max_hue_value,
    );
    let c = hsva(
        hue,
        0.5,
        1.0,
        1.0 - 0.5,
    );
    draw.line()
        .start(Vec2::new(0.0, 0.0))
        .end(Vec2::new(10.0, 10.0))
        .stroke_weight(1.0)
        .color(c);
    draw.to_frame(app, &frame).unwrap();
}
