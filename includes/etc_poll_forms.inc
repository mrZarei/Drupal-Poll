<?php

function etc_poll_polling_form($form,&$form_state,$variables){

    $form = array();
    $entity = $variables['#entity'];
    $items = $variables['#items'];
    $field = $variables['#field'];
    if(isset($_SESSION['etc_poll_'.$entity->nid])){
        $delta = $_SESSION['etc_poll_'.$entity->nid];
        drupal_add_js(array('ep'=>array('entity_id' => $entity->nid,'field_name'=>'etc_poll_options','delta'=>$delta)),'setting');
        drupal_add_js(drupal_get_path('module','etc_poll').'/js/etc_poll_set_cookie.js');
        unset($_SESSION['etc_poll_'.$entity->nid]);
        return;
    }
    $options = array();
    foreach ($items as $delta=>$item) {
        $options[$delta] = $item['value'];
    }

    $form['#prefix'] = '<div id="ep-form-wrapper">';
    $form['#suffix'] = '</div>';
    $form['etc_poll_radios'] = array(
        '#type' => 'radios',
        '#title' => '',
        '#options' => $options,
        '#default_value' => 0,
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('vote!'),
    );
    $form_state['entity_id'] = $entity->nid;
    drupal_add_js(array('ep'=>array('entity_id' => $entity->nid,'field_name'=>$field['field_name'])),'setting');
    drupal_add_js(drupal_get_path('module','etc_poll').'/js/etc_poll.js');
    return $form;
}

/**
 * submit for etc_poll_polling_form.
 */
function etc_poll_polling_form_submit($form, &$form_state)
{
    //check if field_name and entity_id has been set
    $field_name = 'etc_poll_options';
    if (isset($form_state['entity_id']) && !empty($form_state['entity_id'])
    ) {
        $delta = $form_state['values']['etc_poll_radios'];
        $table_name = 'field_data_' . $field_name;
        $field_vote = $field_name . '_vote'; //get the vote column in the databse
        $entity_id = $form_state['entity_id'];

        //get the count of selected choice
        $item_vote_count = db_query("SELECT {$field_vote} FROM {$table_name} WHERE entity_id = :nid AND delta = :delta",
            array(':nid' => $entity_id, ':delta' => $delta))->fetchField();
        $item_vote_count = ($item_vote_count != null) ? $item_vote_count : 0;

        //update vote value to one more.
        db_update($table_name)
            ->fields(array(
                $field_vote => $item_vote_count + 1,
            ))
            ->condition('entity_id', $entity_id, '=')
            ->condition('delta', $delta, '=')
            ->execute();
        $_SESSION['etc_poll_'.$entity_id] = $delta;
    }
    return 'Error!';

}

function _etc_poll_render_result($entity_id){
    $content = '';
    $field_name = 'etc_poll_options';
    try {
        if (field_info_field($field_name)) {
            $table = 'field_data_' . $field_name;
            $field_value = $field_name . '_value';
            $field_vote = $field_name . '_vote';
            $options = db_query("SELECT * FROM {$table} WHERE entity_id = :nid ORDER BY delta", array(':nid' => $entity_id));
            $items = array();
            $total_vote = db_query("SELECT SUM($field_vote) FROM {$table} WHERE entity_id = :nid", array(':nid' => $entity_id))->fetchField();
            $total_vote = ($total_vote != null) ? $total_vote : 0;
            foreach ($options as $option) {
                $delta = $option->delta;
                $vote_count = $option->$field_vote;
                $percentage = ($total_vote) ? round($vote_count * 100 / $total_vote) : 0;
                $variables = array(
                    '#entity_id' => $entity_id,
                    '#delta' => $delta,
                    '#votes_count' => $vote_count,
                    '#txt' => $option->$field_value,
                );
                $markup = theme('etcpoll_row', array('element' => $variables));
                $items[$delta] = array('#markup' => $markup, '#percentage' => $percentage);
            }
            $element[0] = array('#items' => $items, '#total_vote' => $total_vote, '#theme' => 'etcpoll_result');
            return $element;
        }
    }
    catch(Exception $e){
        return "Error!";
    }
    return $content;
}

function _etc_poll_render_question(){
    $questions = db_query("SELECT * From {field_data_etc_poll_question}");
    $header = array('artikel','Fråga','resultat');
    $rows = array();
    foreach ($questions as $quest) {
        $node_id = $quest->entity_id;
        $node = node_load($node_id);
        $rows[] = array(
            $node->title,
            $quest->etc_poll_question_value,
            l('view',"/admin/etc_poll/vote/{$node_id}"),
            );
    }
    return theme('table',array('header'=>$header,'rows'=>$rows));

}