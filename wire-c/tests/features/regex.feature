Feature:
  As a user of cucumber
  I expect the wire to comprehend regex
  So that I know it's safe to use

Scenario: Making sure regex is being parsed
  Given wire server is running
  When this 'scenario' is run
  Then 'scenario' is parsed as a variable

