#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main() {
    ALLEGRO_DISPLAY* display = NULL;

    // Инициализация Allegro
   if (!al_init()) {
       return -1;
    }

    // Создание окна
   display = al_create_display(800, 600);
   if (!display) {
        return -1;
    }

    // Освобождение памяти и завершение программы
   al_destroy_display(display);

return 0;
}
