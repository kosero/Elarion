#include <raylib.h>
#include <string>

#include "ui/button.hxx"

void c_button::draw(t_button &button, Vector2 button_position,
                    Vector2 mouse_position)
{
  float scaled_font_size = button.font_size * button.scale;
  float scaled_padding = button.padding * button.scale;

  Vector2 text_size = MeasureTextEx(button.font_family, button.text.c_str(),
                                    scaled_font_size, 1.0f);
  float width = text_size.x + 2 * scaled_padding;
  float height = text_size.y + 2 * scaled_padding;

  button.size = {width, height};

  Rectangle rect = {button_position.x, button_position.y, width, height};
  button.is_hover = CheckCollisionPointRec(mouse_position, rect);
  button.is_clicked =
      button.is_hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

  Color bg = button.is_hover ? button.hover : button.background;
  DrawRectangleRec(rect, bg);
  DrawRectangleLinesEx(rect, 2, button.border);

  Vector2 text_pos = {button_position.x + (width - text_size.x) / 2,
                      button_position.y + (height - text_size.y) / 2};

  DrawTextEx(button.font_family, button.text.c_str(), text_pos,
             scaled_font_size, 1.0f, button.text_color);
}

bool c_button::is_click(t_button &button, Vector2 button_position,
                        Vector2 mouse_position)
{
  Rectangle rect = {button_position.x, button_position.y, button.size.x,
                    button.size.y};

  button.is_hover = CheckCollisionPointRec(mouse_position, rect);
  button.is_clicked =
      button.is_hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
  return button.is_clicked;
}
