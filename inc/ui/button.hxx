#ifndef UI_BUTTON_HXX
#define UI_BUTTON_HXX

#include <cstdint>
#include <raylib.h>
#include <string>

typedef struct s_button
{
  bool is_hover = false;
  bool is_clicked = false;
  std::string text = "vaybe.";
  int16_t font_size = 9;
  Font font_family = GetFontDefault();
  float scale = 5;
  Vector2 size;
  int16_t padding = 1;
  int16_t margin = 1;
  Color border = {114, 137, 218, 255};
  Color background = {114, 137, 218, 255};
  Color hover = {114, 137, 218, 155};
  Color text_color = {255, 255, 255, 255};

} t_button;

class c_button
{
public:
  void draw(t_button &button, Vector2 button_position, Vector2 mouse_position);
  bool is_click(t_button &button, Vector2 button_position,
                Vector2 mouse_position);
};
#endif
