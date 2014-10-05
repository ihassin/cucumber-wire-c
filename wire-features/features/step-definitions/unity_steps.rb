Given(/^I have Unity copied to "(.*?)"$/) do |folder_name|
  @unity_root = File.expand_path("../../../../" + folder_name, __FILE__)

  expect(File.directory? @unity_root).to eq true
end

Then(/^Unity is invoked and the test is run$/) do
  example_root = "#{@unity_root}/examples/example_3"
  expect(system("cd \"#{example_root}\"; make")).to eq true
end
