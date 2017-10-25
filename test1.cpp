#include <gtest/gtest.h>

#include "markdown.h"
#include "html.h"
#include "buffer.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define READ_UNIT 1024
#define OUTPUT_UNIT 64

TEST(sundown, basics) {

  struct buf *ib, *ob;
	int ret;

	struct sd_callbacks callbacks;
	struct html_renderopt options;
	struct sd_markdown *markdown;

	/* reading everything */
	ib = bufnew(READ_UNIT);
	bufgrow(ib, READ_UNIT);
  bufputs(ib, " * list item ");

	/* performing markdown parsing */
	ob = bufnew(OUTPUT_UNIT);

	sdhtml_renderer(&callbacks, &options, 0);
	markdown = sd_markdown_new(0, 16, &callbacks, &options);

	sd_markdown_render(ob, ib->data, ib->size, markdown);
	sd_markdown_free(markdown);

	/* writing the result to stdout */
	ret = fwrite(ob->data, 1, ob->size, stdout);

	/* cleanup */
	bufrelease(ib);
	bufrelease(ob);

  EXPECT_TRUE(ret >= 0);
}
