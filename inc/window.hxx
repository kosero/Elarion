//
// Created by kosero on 15.07.2025.
//

#ifndef WINDOW_HXX
#define WINDOW_HXX

class window_c {
public:
  explicit window_c(int w = 800, int h = 600, const char *t = "Elarion");

  void                      init() const;
  [[nodiscard]] static bool shouldClose();
  static void               close();

private:
  const char *title;
  const int   width;
  const int   height;
};

#endif // WINDOW_HXX
