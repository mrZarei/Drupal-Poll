This module provides a simple poll setting for each article which has been add to Drupal content;

How does it work:
This module first adds a new field type which is called etc_option. etc_option field type contains a textfield
with unlimited cardinality setting.

After creating the new field type, the module creates two field as well:
* etc_poll_question [textfield]
* etc_poll_options  [etc_option]

etc_poll_question holds the related question to the poll and etc_poll_options holds the choices.

Installation guide:
1-After module has been install and enabled successfully two new field will be added to the article
 content type, which can be found in admin/structure/types/manage/article/fields. Set them in your desire place
 in node form.
2-in the 'manage display' section (admin/structure/types/manage/article/display/) select a proper place
 that you would like the poll field get rendered.
 OBS: etc_poll_options renders all the poll (include question) there is no need to add etc_poll_question field
      in the any display view mode;

3-Give "ETC Poll Result" permission admin page to the administrator (admin/people/permissions)
  to reach to admin/etc_poll/vote.


