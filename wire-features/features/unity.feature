Feature: Being able to develop with a unit testing framework
  As a developer working on this project
  I want to be able to use a unit-testing framework
  So that that I will be able to confidently practice TDD

  Background:
    Given I have Unity copied to "unity-master"

  Scenario: Making sure that the framework is installed
    When I check that it's correctly installed
    Then Unity is invoked and the test is successful

  Scenario: Making sure that a demo program has access to Unity
    Given I have a makefile to test my demo program that uses Unity
    Then tests are invoked and the test is successful
