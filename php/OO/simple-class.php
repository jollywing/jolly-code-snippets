
<?php
class HelloWorld {
  public $var = 'hello, world!';
  function foo(){
    // echo $var; $var is undefined
    // NOTICE: var is not prefixed with $
    echo $this->var . "\n";
  }
}

$class_name = 'HelloWorld';
$instance = new $class_name();
$instance->foo();

// This also can be done: $instance = new HelloWorld();
// NOTICE: no $ in front of HelloWorld!
$inst2 = new HelloWorld();
$inst2->foo();

?>