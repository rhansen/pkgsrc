#!/bin/sh

cd @PREFIX@/share/@RUBY_PKGPREFIX@-redmine/app

GEM_HOME=@PREFIX@/share/@RUBY_PKGPREFIX@-redmine/gems \
  GEM_PATH=@PREFIX@/share/@RUBY_PKGPREFIX@-redmine/gems \
    @RUBY@ bin/rake db:migrate RAILS_ENV=production
