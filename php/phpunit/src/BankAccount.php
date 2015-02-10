<?php
class BankAccount {
    private $value;             // default to 0

    public function __construct($n = 0){
        if($n < 0){
            throw new InvalidArgumentException('Account value can not be negative', 10);
        }
        $this->value = $n;
    }
    
    public function value(){
        return $this->value;
    }

    public function deposit($ammount) {
        $this->value += $ammount;
    }
}
?>