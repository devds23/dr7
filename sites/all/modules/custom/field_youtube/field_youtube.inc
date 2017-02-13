<?php
$value = $form_state['values'][$form_state['youtube_field_name']][LANGUAGE_NONE][0]['user_input'];
$entity = $form_state['build_info']['args'][0];

$exist_data =  $entity->$form_state['youtube_field_name'];

$exist_data = isset($exist_data[LANGUAGE_NONE][0]) ? $exist_data[LANGUAGE_NONE][0] : NULL;


$video_id = field_youtube_get_value($value);

if ($exist_data != NULL && $exist_data['youtube_id'] == $video_id) {
  $form_state['values'][$form_state['youtube_field_name']][LANGUAGE_NONE][0]['fid'] = $exist_data['fid'];
  $form_state['values'][$form_state['youtube_field_name']][LANGUAGE_NONE][0]['youtube_id'] = $exist_data['youtube_id'];
  return;
}
dpm('new');

$entity_type = $form_state['build_info']['args'][1];
$entity_id = entity_extract_ids($entity_type, $entity);

// Delete old image is it exist.
if(isset($exist_data['fid'])){
  $old_file = file_load($exist_data['fid']);
  if(is_object($old_file)) {
    file_usage_delete($old_file, 'field_youtube', $entity_type, $entity_id[0]);
    file_delete($old_file);
  }
}

// Create new file.
$image = @file_get_contents("https://img.youtube.com/vi/" . $video_id . "/0.jpg");
$destination = 'public://youtube_' . $video_id . '.jpg';
if($image !== FALSE){
  $file = file_save_data($image, $destination);
  $file->status = 0; // 1
  $file = file_save($file);
  $form_state['values'][$form_state['youtube_field_name']][LANGUAGE_NONE][0]['fid'] = $file->fid;

  file_usage_add($file, 'field_youtube', $entity_type, $entity_id[0]);
}
else{
  $form_state['values'][$form_state['youtube_field_name']][LANGUAGE_NONE][0]['fid'] = NULL;
}

$form_state['values'][$form_state['youtube_field_name']][LANGUAGE_NONE][0]['youtube_id'] = $video_id;


