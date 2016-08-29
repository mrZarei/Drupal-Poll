<?php

function theme_etcpoll_form($variables){
    $items = array();
    $entity = $variables['#entity'];
    $question = $variables['#question'];
    $poll = drupal_get_form('etc_poll_polling_form',$variables);
    $items[] = "<h1 class='etc-poll-question'>{$question}</h1>";
    $items[] = drupal_render($poll);
    $items[] = drupal_render(_etc_poll_render_result($entity->nid));
    return join('',$items);
}

function theme_etcpoll_result($variables)
{
    $items = $variables['element']['#items'];
    $total_vote_count = '';
    if (isset($variables['element']['#total_vote'])) {
        $total_vote_count = format_plural($variables['element']['#total_vote'], 'Totalt 0 röster', 'Totalt @count röster');
    }
    $output = array();
    $output[] = "<div id='ep-result-wrapper'>";
    foreach ($items as $delta => $item) {
        $bar = '';
        if (isset($item['#percentage'])) {
            $percentage = round($item['#percentage']);
            $bar = "<div class='etc-poll-percentage' style='width: {$percentage}%'></div>";
        }
        $output[] = "<div class='etc-poll-item'><div class='etc-poll-data clearfix'>{$item['#markup']}$bar</div></div>";
    }
    $output[] = "<div class='etc-poll-total-vote-count'>$total_vote_count</div>";
    $output[] ="</div>";
    return join('', $output);
}

function theme_etcpoll_row($variables) {
    $entity_id  = intval($variables['element']['#entity_id']);
    $delta      = intval($variables['element']['#delta']);
    $vote_count = isset($variables['element']['#votes_count']) ? strip_tags($variables['element']['#votes_count']) : NULL;
    $txt        = strip_tags($variables['element']['#txt']);
    $output = "<div class='choice' id='etc-poll-$entity_id-$delta'>(";
    $output .=!empty($vote_count) ? $vote_count.') ' : '0) ';
    $output .= "$txt</div>";
    return $output;
}





