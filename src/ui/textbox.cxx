#include <raylib.h>

#include "ui/textbox.hxx"

void c_textbox::draw(t_textbox &textbox, Vector2 position)
{
  Color bg_color = textbox.is_focused ? textbox.focused_background_color
                                      : textbox.background_color;
  DrawRectangleV(position, textbox.size, bg_color);

  DrawRectangleLines(static_cast<int>(position.x), static_cast<int>(position.y),
                     static_cast<int>(textbox.size.x),
                     static_cast<int>(textbox.size.y), textbox.border_color);

  Vector2 text_pos = {position.x + textbox.padding,
                      position.y + (textbox.size.y - textbox.font_size) / 2.0f};

  DrawTextEx(textbox.font_family, textbox.text.c_str(), text_pos,
             (float)textbox.font_size, 1, textbox.text_color);

  if (textbox.is_focused)
  {
    int text_width = static_cast<int>(MeasureTextEx(textbox.font_family,
                                                    textbox.text.c_str(),
                                                    (float)textbox.font_size, 1)
                                          .x);

    int cursor_x = static_cast<int>(position.x) + textbox.padding + text_width;
    int cursor_y1 = static_cast<int>(position.y) + textbox.padding;
    int cursor_y2 =
        static_cast<int>(position.y + textbox.size.y) - textbox.padding;

    DrawLine(cursor_x, cursor_y1, cursor_x, cursor_y2, textbox.text_color);
  }
}

void c_textbox::update(t_textbox &textbox, Vector2 position,
                       Vector2 mouse_position)
{
  Rectangle box_rect = {position.x, position.y, textbox.size.x, textbox.size.y};

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    textbox.is_focused = CheckCollisionPointRec(mouse_position, box_rect);
  }

  if (!textbox.is_focused)
    return;

  int key = GetCharPressed();
  while (key > 0)
  {
    if ((key >= 32) && (key <= 126))
    {
      if (textbox.text.size() < MAX_LENGTH)
        textbox.text.push_back(static_cast<char>(key));
    }
    key = GetCharPressed();
  }

  if (IsKeyPressed(KEY_BACKSPACE) && !textbox.text.empty())
  {
    textbox.text.pop_back();
  }
}

bool c_textbox::is_enter_pressed(t_textbox &textbox)
{
  return textbox.is_focused && IsKeyPressed(KEY_ENTER) && !textbox.text.empty();
}
