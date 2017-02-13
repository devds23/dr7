<?php

$plugin = array(
  'title' => t('Second Layout'), // Название плагина.
  'icon' => 'second_layout.png', // Графическое представление плагина. Используется для демонстрации регионов при выборе макета.
  'category' => t('Pets owners'),
  'theme' => 'mybartik_second_layout', // Шаблон плагина. При создании шаблона все подчеркивания необходимо заменить на тирэ.
  'css' => 'second_layout.css', // CSS файл, содержащий стили для нашего плагина при отображении и редактировании панели.
  'admin theme' => 'mybartik_admin_second_layout',
  'admin css' => 'second_layout_admin.css', // Этот CSS файл особенно полезен. Он подключается только в административных разделах сайта, что позволяет избежать некоторых проблем с отображением панели.
  'regions' => array('middle' => t('Middle column')),
);
