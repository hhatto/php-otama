<?php
class OtamaTest extends PHPUnit_Framework_TestCase
{
    public function testOtamaIsLoaded()
    {
        $this->assertEquals(true, extension_loaded("otama"));
    }

    public function testOtamaClassExists()
    {
        $this->assertEquals(true, class_exists("Otama"));
    }

    public function testOtamaOpenMethodExists()
    {
        $reflection = new ReflectionClass("Otama");
        $this->assertEquals(true, $reflection->hasMethod("open"));
    }
}
