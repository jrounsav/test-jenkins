Feature:
  Testing the activity stream

  @api @wip
  Scenario: Check activity stream page
    Given I visit "/api/v1/activities"
     Then I should see "John created Software Project: Windows 7"

  @api @misc_first
  Scenario: Check that only public messages are displayed on /activity.json
    Given I am logging in as "john"
     When I create a new "blog" entry with the name "public unique title"
      And I change privacy of the site "obama" to "Invite only during site creation. "
      And I create a new "blog" entry with the name "private different title" in the group "obama"
      And I click "Log out"
     When I visit "api/v1.0/activities"
     Then I should see the following message <json>:
          | !title | public unique title     |
      And I should not see the following message <json>:
          | !title | private different title |
          # Make the VSite public again.
      And I am logging in as "john"
      And I change privacy of the site "obama" to "Public on the web. "
