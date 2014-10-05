Given(/^I have Unity copied to "(.*?)"$/) do |folder_name|
  @unity_root = File.expand_path("../../../../" + folder_name, __FILE__)
end

When(/^I check that it's correctly installed$/) do
  expect(File.directory? @unity_root).to eq true
end

Then(/^Unity is invoked and the test is successful$/) do
  example_root = "#{@unity_root}/examples/example_3"
  expect(system("cd \"#{example_root}\"; make")).to eq true
end

Given(/^I have a makefile to test my demo program that uses Unity$/) do
  @test_root = File.expand_path("../../../../wire-c/wire-c/", __FILE__)
  @makefile = File.expand_path("../../../../wire-c/wire-c/" + 'makefile', __FILE__)
  expect(File.exist? @makefile).to eq true
end

Then(/^tests are invoked and the test is successful$/) do
  expect(system("cd \"#{@test_root}\"; make")).to eq true
  expect(system("cd \"#{@test_root}\"; make clean")).to eq true
end
