<?php
class BankAccountTest extends PHPUnit_Framework_TestCase
{
    public function testNewAccount(){
        $account1 = new BankAccount();
        $this->assertEquals(0, $account1->value());
        $account2 = new BankAccount(10);
        $this->assertEquals(10, $account2->value());
    }

    /**
     * @test
     * @expectedException InvalidArgumentException
     * @expectedExceptionMessage Account value
     */
    public function newAccountException() {
        $r = 0 - rand(10, 100);
        $account = new BankAccount($r);
    }
    
    public function testDeposit(){
        $account = new BankAccount();
        $account->deposit(10);
        $this->assertEquals(10, $account->value());
        $account->deposit(-5);
        $this->assertEquals(5, $account->value());
    }
}
?>