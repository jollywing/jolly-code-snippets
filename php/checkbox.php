<html>
  <head>
    <title>CheckBox</title>
  </head>
  <body>
    <h1>CheckBox</h1>

    <?php
    if(isset($_POST['export'])){
      echo '<p>The value of select_date_box is '.$_POST['select_date_box']."<br/>\n";
      echo 'The value of select_cat_box is '.$_POST['select_cat_box']."</p>\n";
      if($_POST['select_date_box'] == 'select_by_date'){
        echo '<p>Date Limit: ';
        echo 'From '.$_POST['start_year'].'-'.$_POST['start_month'];
        echo ' To '.$_POST['end_year'].'-'.$_POST['end_month']."</p>\n";
      }
      if($_POST['select_cat_box'] == 'select_by_cat'){
        echo '<p>Category Limit: '. $_POST['category']."</p>\n";
      }
    }
    ?>

    <form name='export_article' action='checkbox.php' method='POST'>
      <p>
      <input type='checkbox' value='select_by_date' name='select_date_box' />限定日期:<br>
      起始年月：
      <select name='start_year'>
        <option value='2010'>2010</option>
        <option value='2011'>2011</option>
        <option value='2012'>2012</option>
      </select>年
      <select name='start_month'>
        <option value='1'>1</option>
        <option value='2'>2</option>
        <option value='3'>3</option>
        <option value='4'>4</option>
        <option value='5'>5</option>
        <option value='6'>6</option>
        <option value='7'>7</option>
        <option value='8'>8</option>
        <option value='9'>9</option>
        <option value='10'>10</option>
        <option value='11'>11</option>
        <option value='12'>12</option>
      </select>月<br>
      结束年月：
      <select name='end_year'>
        <option value='2010'>2010</option>
        <option value='2011'>2011</option>
        <option value='2012'>2012</option>
      </select>年
      <select name='end_month'>
        <option value='1'>1</option>
        <option value='2'>2</option>
        <option value='3'>3</option>
        <option value='4'>4</option>
        <option value='5'>5</option>
        <option value='6'>6</option>
        <option value='7'>7</option>
        <option value='8'>8</option>
        <option value='9'>9</option>
        <option value='10'>10</option>
        <option value='11'>11</option>
        <option value='12'>12</option>
      </select>月<br>
      </p>

      <p>
      <input type='checkbox' value='select_by_cat' name='select_cat_box' checked />限定分类:<br>
      文章类别:
      <select name='category'>
        <option value='Vim'>Vim</option>
        <option value='Emacs'>Emacs</option>
        <option value='FreeBSD'>FreeBSD</option>
      </select>
      </p>

      <p><input type='submit' name='export' value='export'/></p>
    </form>
  </body>
</html>
