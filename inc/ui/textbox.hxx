#ifndef UI_TEXTBOX_HXX
#define UI_TEXTBOX_HXX

#include <raylib.h>
#include <string>

constexpr size_t MAX_LENGTH = 256;

typedef struct s_textbox
{
  bool is_focused = false;
  std::string text = "";
  int16_t font_size = 20;
  Font font_family = GetFontDefault();
  Vector2 size = {0, 0};
  Color border_color = {114, 137, 218, 255};
  Color background_color = {200, 200, 200, 255};
  Color focused_background_color = {230, 230, 230, 255};
  Color text_color = BLACK;
  int16_t padding = 10;
} t_textbox;

class c_textbox
{
public:
  void draw(t_textbox &textbox, Vector2 position);
  void update(t_textbox &textbox, Vector2 position, Vector2 mouse_position);
  bool is_enter_pressed(t_textbox &textbox);
};

#endif
