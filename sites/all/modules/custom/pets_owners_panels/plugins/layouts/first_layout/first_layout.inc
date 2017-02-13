<?php
/**
 * @file
 *
 * Array of layouts configs
 */

$plugin = array(
  'title' => t('First Layout'), // Название плагина.
  'icon' => 'first_layout.png', // Графическое представление плагина. Используется для демонстрации регионов при выборе макета.
  'category' => t('Pets owners'),
  'theme' => 'pets_owners_panels_first_layout', // Шаблон плагина. При создании шаблона все подчеркивания необходимо заменить на тирэ.
  'css' => 'first_layout.css', // CSS файл, содержащий стили для нашего плагина при отображении и редактировании панели.
  'admin css' => 'first_layout_admin.css', // Этот CSS файл особенно полезен. Он подключается только в административных разделах сайта, что позволяет избежать некоторых проблем с отображением панели.
  'admin theme' => 'pets_owners_panels_admin_first_layout',
  'regions' => array(
    'left' => t('Left side'), // Объявление "main" региона.
    'right' => t('Right side'), // Оъявление "right" региона.
  ),
);
